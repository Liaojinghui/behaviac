/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Tencent is pleased to support the open source community by making behaviac available.
//
// Copyright (C) 2015 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the BSD 3-Clause License (the "License"); you may not use this file except in compliance with
// the License. You may obtain a copy of the License at http://opensource.org/licenses/BSD-3-Clause
//
// Unless required by applicable law or agreed to in writing, software distributed under the License is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and limitations under the License.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "behaviac/base/core/thread/wrapper.h"
#include "behaviac/base/core/thread/mutex.h"
#include "behaviac/base/core/thread/thread.h"

#if !BEHAVIAC_COMPILER_MSVC
#include <unistd.h>

namespace behaviac
{
    namespace Thread
    {
        void Sleep(long millis)
        {
            //sleep(millis);
            //printf("sleep %ld\n", millis);
            clock_t goal = millis + clock();

            while (goal > clock());
        }
    }

    // Returns a new value of i
    Atomic32 AtomicInc(volatile Atomic32& i)
    {
        __sync_fetch_and_add(&i, 1);
        return i;
    }

    Atomic32 AtomicDec(volatile Atomic32& i)
    {
        __sync_fetch_and_sub(&i, 1);
        return i;
    }

    void ThreadInt::Init()
    {
        if (!m_inited)
        {
            m_inited = true;
        }
    }

    ThreadInt::ThreadInt()
    {
        //this is a globle, m_inited is 0 anyway
        this->Init();
    }

    ThreadInt::~ThreadInt()
    {
        m_inited = false;
    }

    //void ThreadInt::set(long v)
    //{
    //	{
    //		behaviac::ScopedLock lock(m_csMemory);
    //		m_value = v;
    //	}
    //}

    long ThreadInt::value() const
    {
        return m_value;
    }

    long ThreadInt::operator++()
    {
        this->Init();

        //{
        //	behaviac::ScopedLock lock(m_csMemory);
        //	m_value++;
        //}

        return m_value;
    }

    void ThreadInt::operator--()
    {
        this->Init();

        //{
        //	behaviac::ScopedLock lock(m_csMemory);
        //	m_value--;
        //}
    }
}
#endif//#if !BEHAVIAC_COMPILER_MSVC
