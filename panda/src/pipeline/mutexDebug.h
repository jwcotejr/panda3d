// Filename: mutexDebug.h
// Created by:  drose (13Feb06)
//
////////////////////////////////////////////////////////////////////
//
// PANDA 3D SOFTWARE
// Copyright (c) Carnegie Mellon University.  All rights reserved.
//
// All use of this software is subject to the terms of the revised BSD
// license.  You should have received a copy of this license along
// with this source code in a file named "LICENSE."
//
////////////////////////////////////////////////////////////////////

#ifndef MUTEXDEBUG_H
#define MUTEXDEBUG_H

#include "pandabase.h"
#include "mutexTrueImpl.h"
#include "conditionVarImpl.h"
#include "thread.h"
#include "namable.h"

#ifdef DEBUG_THREADS

#if defined(SIMPLE_THREADS) && defined(SIMPLE_THREADS_NO_MUTEX)
// In this mode, we don't actually lock and unlock a mutex.  We just
// wave at them as they go by.  This actually involves a bit more
// work, here in the debug mode, than a real mutex, because we have to
// track all the threads that failed to lock the mutex.
#define PHONY_MUTEX
#endif

////////////////////////////////////////////////////////////////////
//       Class : MutexDebug
// Description : This class implements a standard mutex the hard way,
//               by doing everything by hand.  This does allow fancy
//               things like deadlock detection, however.
////////////////////////////////////////////////////////////////////
class EXPCL_PANDA_PIPELINE MutexDebug : public Namable {
protected:
  MutexDebug(const string &name, bool allow_recursion);
  virtual ~MutexDebug();
private:
  INLINE MutexDebug(const MutexDebug &copy);
  INLINE void operator = (const MutexDebug &copy);

PUBLISHED:
  BLOCKING INLINE void lock() const;
  BLOCKING INLINE void lock(Thread *current_thread) const;
  INLINE void elevate_lock() const;
  INLINE void release() const;
  INLINE bool debug_is_locked() const;

  virtual void output(ostream &out) const;

  typedef void VoidFunc();

private:
  void do_lock();
  void do_release();
  bool do_debug_is_locked() const;

  void report_deadlock(Thread *this_thread);

private:
  INLINE static MutexTrueImpl *get_global_lock();

  bool _allow_recursion;
  Thread *_locking_thread;
  int _lock_count;
#ifdef PHONY_MUTEX
  typedef pmap<Thread *, int> MissedThreads;
  MissedThreads _missed_threads;
#endif

  ConditionVarImpl _cvar_impl;

  static MutexTrueImpl *_global_lock;

  friend class ConditionVarDebug;
  friend class ConditionVarFullDebug;
};

INLINE ostream &
operator << (ostream &out, const MutexDebug &m) {
  m.output(out);
  return out;
}

#include "mutexDebug.I"

#endif  //  DEBUG_THREADS

#endif
