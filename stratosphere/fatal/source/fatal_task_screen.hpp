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
 
#pragma once
#include <switch.h>
#include <stratosphere.hpp>
#include "fatal_task.hpp"

class ShowFatalTask : public IFatalTask {
    private:
        Event *battery_event;
        ViDisplay display;
        ViLayer layer;
        NWindow win;
        Framebuffer fb;
    private:
        Result SetupDisplayInternal();
        Result SetupDisplayExternal();
        Result PrepareScreenForDrawing();
        Result ShowFatal();
    public:
        ShowFatalTask(FatalContext *ctx, u64 title_id, Event *evt) : IFatalTask(ctx, title_id), battery_event(evt) { }
        virtual Result Run() override;
        virtual const char *GetName() const override {
            return "ShowFatal";
        }
};

class BacklightControlTask : public IFatalTask {
    private:
        void TurnOnBacklight();
    public:
        BacklightControlTask(FatalContext *ctx, u64 title_id) : IFatalTask(ctx, title_id) { }
        virtual Result Run() override;
        virtual const char *GetName() const override {
            return "BacklightControlTask";
        }
};