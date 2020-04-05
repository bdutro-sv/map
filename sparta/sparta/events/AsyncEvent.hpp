// <AsyncEvent.hpp> -*- C++ -*-

#pragma once

#include "sparta/events/Event.hpp"

namespace sparta
{
    /**
     * \class AsyncEvent
     * \brief In a multi-threaded sim environment, this event is used to schedule an event asynchronously
     *
     * AsyncEvents are intended to be used by threads other than the main
     * scheduling thread (i.e., the thread that runs Scheduler::run()) that
     * wants to schedule events on the scheduler. They are asynchronous in the
     * sense that they are not necessarily scheduled right away when their
     * schedule() method is called. The relative delay is relative to the time
     * when the events are actually scheduled. This means that if a delay of 100
     * is specified, the event will be scheduled at least 100 clocks from now.
     */
    template<SchedulingPhase sched_phase_T = SchedulingPhase::Tick>
    class AsyncEvent : public Event<sched_phase_T>
    {
    public:
        AsyncEvent(TreeNode *event_set,
                   const std::string &name,
                   const SpartaHandler &consumer_event_handler,
                   Clock::Cycle delay = 0)
        : Event<sched_phase_T>(event_set, name, consumer_event_handler, delay) { }

        /**
         * \brief Asynchronously schedule this event on an relative tick
         * \param rel_tick Delay relative to the time the event is actually scheduled
         * \param scheduler The scheduler that the event will be scheduled on
         */
        virtual void scheduleRelativeTick(Scheduler::Tick rel_tick,
                                          Scheduler *scheduler) override
        {
            sparta_assert(scheduler != nullptr);
            scheduler->scheduleAsyncEvent(this, rel_tick);
        }

        /**
         * \brief Cancel this event. This method should only be called from the
         *        main scheduler thread.
         */
        void cancel()
        {
            sparta_assert(Scheduleable::scheduler_ != nullptr);
            Scheduleable::scheduler_->cancelAsyncEvent(this);
        }
    };
} /* namespace sparta */
