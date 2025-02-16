/*
 * Copyright (c) 2021, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "TimelineContainer.h"
#include "TimelineView.h"
#include <LibGUI/Layout.h>

namespace Profiler {

TimelineContainer::TimelineContainer(GUI::Widget& header_container, TimelineView& timeline_view)
{
    m_header_container = header_container;
    m_timeline_view = timeline_view;
    add_child(header_container);
    add_child(timeline_view);
    header_container.move_to_back();
    timeline_view.move_to_back();
}

TimelineContainer::~TimelineContainer()
{
}

void TimelineContainer::did_scroll()
{
    AbstractScrollableWidget::did_scroll();
    update_widget_positions();
}

void TimelineContainer::update_widget_positions()
{
    m_header_container->move_to(0, -vertical_scrollbar().value());
    m_timeline_view->move_to(m_header_container->width() + -horizontal_scrollbar().value(), -vertical_scrollbar().value());
}

void TimelineContainer::update_widget_sizes()
{
    {
        m_timeline_view->do_layout();
        auto preferred_size = m_timeline_view->layout()->preferred_size();
        m_timeline_view->resize(preferred_size);
        set_content_size(preferred_size);
    }

    {
        m_header_container->do_layout();
        auto preferred_size = m_header_container->layout()->preferred_size();
        m_header_container->resize(preferred_size);
    }
}

void TimelineContainer::resize_event(GUI::ResizeEvent& event)
{
    AbstractScrollableWidget::resize_event(event);
    update_widget_sizes();
}

}
