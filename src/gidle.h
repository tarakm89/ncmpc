/* ncmpc (Ncurses MPD Client)
   (c) 2004-2017 The Music Player Daemon Project
   Project homepage: http://musicpd.org

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

   - Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

   - Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef MPD_GLIB_SOURCE_H
#define MPD_GLIB_SOURCE_H

#include <mpd/client.h>

typedef void (*mpd_glib_callback_t)(enum mpd_error error,
				    enum mpd_server_error server_error,
				    const char *message,
				    enum mpd_idle events, void *ctx);

struct mpd_glib_source;

struct mpd_glib_source *
mpd_glib_new(struct mpd_connection *connection,
	     mpd_glib_callback_t callback, void *callback_ctx);

void
mpd_glib_free(struct mpd_glib_source *source);

/**
 * Enters idle mode.
 *
 * @return true if idle mode has been entered, false if not
 * (e.g. blocked during the callback, or I/O error)
 */
bool
mpd_glib_enter(struct mpd_glib_source *source);

/**
 * Leaves idle mode and invokes the callback if there were events.
 *
 * @return true on success, false if this object was deleted by the
 * callback
 */
bool
mpd_glib_leave(struct mpd_glib_source *source);

#endif
