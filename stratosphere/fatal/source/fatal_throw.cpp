/*
 * Copyright (c) 2018 Atmosphère-NX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#include <switch.h>
#include "fatal_throw.hpp"
#include "fatal_event_manager.hpp"
#include "fatal_task.hpp"
#include "fatal_config.hpp"

static bool g_thrown = false;

static Result SetThrown() {
    /* This should be fine, since fatal only has a single IPC thread. */
    if (g_thrown) {
        return FatalResult_AlreadyThrown;
    }
    
    g_thrown = true;
    return 0;
}

Result ThrowFatalForSelf(u32 error) {
    u64 pid = 0;
    FatalCpuContext ctx = {0};
    
    svcGetProcessId(&pid, CUR_PROCESS_HANDLE);
    return ThrowFatalImpl(error, pid, FatalType_ErrorScreen, &ctx);
}

Result ThrowFatalImpl(u32 error, u64 pid, FatalType policy, FatalCpuContext *cpu_ctx) {
    Result rc = 0;
    FatalContext ctx;
    ctx.error_code = error;
    ctx.cpu_ctx = *cpu_ctx;
    
    /* Get config. */
    const FatalConfig *config = GetFatalConfig();
    
    /* Get title id. On failure, it'll be zero. */
    u64 title_id = 0;
    pminfoGetTitleId(&title_id, pid);
    
    switch (policy) {
        case FatalType_ErrorReport:
            /* TODO: Don't write an error report. */
            break;
        case FatalType_ErrorReportAndErrorScreen:
        case FatalType_ErrorScreen:
            {
                /* Ensure we only throw once. */
                if (R_FAILED((rc = SetThrown()))) {
                    return rc;
                }
                
                /* Signal that fatal is about to happen. */
                GetEventManager()->SignalEvents();
                
                /* Create events. */
                Event erpt_event;
                Event battery_event;
                if (R_FAILED(eventCreate(&erpt_event, false)) || R_FAILED(eventCreate(&battery_event, false))) {
                    std::abort();
                }
                
                /* Run tasks. */
                if (config->transition_to_fatal) {
                    RunFatalTasks(&ctx, title_id, policy == FatalType_ErrorReportAndErrorScreen, &erpt_event, &battery_event);
                } else {
                    /* If flag is not set, don't show the fatal screen. */
                    return 0;
                }
                
            }
            break;
        default:
            /* N aborts here. Should we just return an error code? */
            std::abort();
    }
    
    return 0;
}
