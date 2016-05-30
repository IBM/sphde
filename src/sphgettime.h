/*
 * Copyright (c) 2016 IBM Corporation.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Contributors:
 *     IBM Corporation, Paul Clarke - New API.
 */

#ifndef __SPH_GETTIME_H_
#define __SPH_GETTIME_H_

/*!
 * \file  sphgettime.h
 * \brief Functions to convert time stamp (sphtimer_t) values to
 * struct timespec value format with clock_gettime() epoch.
 *
 * This API is intended to support post processing time stamps
 * (including those generated by SPHLFLogger_t and SPHSinglePCQueue_t)
 * into clock_gettime() epoch and related formatted time values.
 *
 * It is not intended as an exact replacement for clock_gettime()
 * because it may not include any NTP corrections for example,
 * but it will close and will be monotonic.
 */

#include <time.h>
#include <sphtimer.h>

#ifdef __cplusplus
#define __C__ "C"
#else
#define __C__
#endif

/*!
 * \brief Return the timebase converted to clock_gettime struct timespec.
 *
 * Returns a fast emulation of the values returned by clock_gettime computed
 * from a queried machine timebase register value.
 *
 * @param tp address of the struct timespec buffer.
 * @return The timebase converted to clock_gettime in struct timespec.
 */

extern __C__ int
sphgettime (struct timespec *tp);

/*!
 * \brief Return the timebase-to-gettimeofday conversion factor.
 *
 * As the timebase (sphtimer_t) is a fast hardware timer or something
 * similar to "uptime" we need to allow for logs that persist across
 * reboot. By saving this conversion factor in the log we can use it
 * during post processing of the log to get the corrected clock_gettime
 * value for formatted time values.
 *
 * This allow the logger to run as fast as possible by postponing the
 * timebase to clock_gettime conversion until post processing.
 *
 * @return The timebase to clock_gettime conversion factor.
 */

extern __C__ sphtimer_t
sphget_gettime_conv_factor (void);

/*!
 * \brief Return the timebase converted to clock_gettime struct timeval.
 *
 * As the timebase (sphtimer_t) is a fast hardware timer or something
 * similar to "uptime" we need to allow for logs that persist across
 * reboot. By saving the conversion factor (via sphget_gettime_conv_factor())
 * in the log we can use it (via this API) during post processing of
 * the log to get the corrected clock_gettime value for formatted time
 * values.
 *
 * @param tp address of the struct timespec buffer.
 * @param timestamp value via sphgettimer().
 * @param tb2gettime_factor timebase to clock_gettime conversion factor.
 * @return The timebase converted to clock_gettime in struct timespec.
 */

extern __C__ int
sphtb2gettime_withfactor (struct timespec *tp,
		sphtimer_t timestamp,
		sphtimer_t tb2gettime_factor);

#endif /* __SPH_GETTIME_H */
