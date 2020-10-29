﻿/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */

#pragma once
#include <aws/batch/Batch_EXPORTS.h>

namespace Aws
{
namespace Utils
{
namespace Json
{
  class JsonValue;
  class JsonView;
} // namespace Json
} // namespace Utils
namespace Batch
{
namespace Model
{

  /**
   * <p>The retry strategy associated with a job.</p><p><h3>See Also:</h3>   <a
   * href="http://docs.aws.amazon.com/goto/WebAPI/batch-2016-08-10/RetryStrategy">AWS
   * API Reference</a></p>
   */
  class AWS_BATCH_API RetryStrategy
  {
  public:
    RetryStrategy();
    RetryStrategy(Aws::Utils::Json::JsonView jsonValue);
    RetryStrategy& operator=(Aws::Utils::Json::JsonView jsonValue);
    Aws::Utils::Json::JsonValue Jsonize() const;


    /**
     * <p>The number of times to move a job to the <code>RUNNABLE</code> status. You
     * may specify between 1 and 10 attempts. If the value of <code>attempts</code> is
     * greater than one, the job is retried on failure the same number of attempts as
     * the value.</p>
     */
    inline int GetAttempts() const{ return m_attempts; }

    /**
     * <p>The number of times to move a job to the <code>RUNNABLE</code> status. You
     * may specify between 1 and 10 attempts. If the value of <code>attempts</code> is
     * greater than one, the job is retried on failure the same number of attempts as
     * the value.</p>
     */
    inline bool AttemptsHasBeenSet() const { return m_attemptsHasBeenSet; }

    /**
     * <p>The number of times to move a job to the <code>RUNNABLE</code> status. You
     * may specify between 1 and 10 attempts. If the value of <code>attempts</code> is
     * greater than one, the job is retried on failure the same number of attempts as
     * the value.</p>
     */
    inline void SetAttempts(int value) { m_attemptsHasBeenSet = true; m_attempts = value; }

    /**
     * <p>The number of times to move a job to the <code>RUNNABLE</code> status. You
     * may specify between 1 and 10 attempts. If the value of <code>attempts</code> is
     * greater than one, the job is retried on failure the same number of attempts as
     * the value.</p>
     */
    inline RetryStrategy& WithAttempts(int value) { SetAttempts(value); return *this;}

  private:

    int m_attempts;
    bool m_attemptsHasBeenSet;
  };

} // namespace Model
} // namespace Batch
} // namespace Aws
