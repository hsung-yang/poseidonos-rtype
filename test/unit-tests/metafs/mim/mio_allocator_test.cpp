/*
 *   BSD LICENSE
 *   Copyright (c) 2021 Samsung Electronics Corporation
 *   All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *     * Neither the name of Samsung Electronics Corporation nor the names of
 *       its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "src/metafs/mim/mio_allocator.h"

#include <gtest/gtest.h>

#include "test/unit-tests/metafs/mim/mpio_allocator_mock.h"

using ::testing::NiceMock;

namespace pos
{
TEST(MioAllocator, CheckMioAllocatorCanAllocAndRelease)
{
    const uint32_t COUNT = 10;
    const int arrayId = 0;
    NiceMock<MockMpioAllocator>* mpioAllocator = new NiceMock<MockMpioAllocator>(COUNT);
    Mio* mioList[10] = {
        0,
    };
    MioAllocator* mioAllocator = new MioAllocator(mpioAllocator, COUNT);

    EXPECT_EQ(mioAllocator->GetFreeCount(), COUNT);
    EXPECT_EQ(mioAllocator->GetCapacity(), COUNT);

    for (uint32_t index = 0; index < COUNT; index++)
    {
        mioList[index] = mioAllocator->TryAlloc();
        ASSERT_NE(mioList[index], nullptr);
    }

    EXPECT_TRUE(mioAllocator->IsEmpty());
    EXPECT_EQ(mioAllocator->TryAlloc(), nullptr);

    for (uint32_t index = 0; index < COUNT; index++)
    {
        mioAllocator->Release(mioList[index]);
    }

    EXPECT_EQ(mioAllocator->GetFreeCount(), COUNT);
    EXPECT_NO_FATAL_FAILURE(mioAllocator->Release(nullptr));

    delete mioAllocator;
    delete mpioAllocator;
}
} // namespace pos