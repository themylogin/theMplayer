#!/usr/bin/env python2
# -*- coding: utf-8 -*-
def natural_sort(list):
    import re
    return sorted(list, key=lambda key: [int(text) if text.isdigit() else text.lower() for text in re.split("([0-9]+)", key)])

class MPlayerShell:
    PLAYLIST_INACTIVE = 0
    PLAYLIST_CURRENT = 1
    PLAYLIST_SCHEDULED = 2

    def __init__(self, filename, populate_playlist):
        import os, os.path, threading

        self.directory = os.path.dirname(os.path.abspath(filename))
        self.current_file = os.path.basename(os.path.abspath(filename))
        playlist_files = natural_sort(filter(lambda x: not os.path.isdir(x) and os.path.splitext(x)[1].lower()[1:] in ["avi", "m2ts", "mkv", "mp4"], os.listdir(self.directory))) if populate_playlist else [self.current_file]

        self.playlist = []
        reached_current_file = False
        for file in playlist_files:
            state = self.PLAYLIST_INACTIVE
            if file == self.current_file:
                state = self.PLAYLIST_CURRENT
                reached_current_file = True
            elif reached_current_file:
                state = self.PLAYLIST_SCHEDULED

            self.playlist.append({
                "file"      :   file,
                "length"    :   -1,
                "state"     :   state,
            })
        threading.Thread(target=self.identify_playlist).start()

        self.current_file_position = -1

        self.init_x11()
        self.init_gtk()

        self.play()

    def identify_playlist(self):
        import os.path
        for file in self.playlist:
            if file["state"] in [self.PLAYLIST_CURRENT, self.PLAYLIST_SCHEDULED]:
                try:
                    file["length"] = self.get_file_length(os.path.join(self.directory, file["file"]))
                except:
                    file["state"] = self.PLAYLIST_INACTIVE

    def get_file_length(self, filename):
        import re, subprocess

        return int(re.search(r"ID_LENGTH=([0-9]+)", subprocess.check_output(["mplayer", "-ao", "null", "-vc", ",", "-vo", "null", "-frames", "0", "-identify", filename], stderr=subprocess.STDOUT)).group(1))

    def init_x11(self):
        from Xlib import X, XK
        from Xlib.display import Display 

        disp = Display()
        root = disp.screen().root
        root.change_attributes(event_mask=X.KeyPressMask)

        self.WINDOW_KEY = disp.keysym_to_keycode(XK.string_to_keysym("n"))
        root.grab_key(self.WINDOW_KEY, X.AnyModifier, 1, X.GrabModeAsync, X.GrabModeAsync)

        import threading
        t = threading.Thread(target=lambda: self.process_x11(disp))
        t.daemon = True
        t.start()
    
    def process_x11(self, disp):
        import gtk
        from Xlib import X

        while True:
            event = disp.next_event()
        
            if event.type == X.KeyPress: 
                keycode = event.detail 
                if keycode == self.WINDOW_KEY:
                    gtk.threads_enter()
                    self.window.set_visible(not self.window.get_visible())
                    gtk.threads_leave()

    def init_gtk(self):
        import pygtk
        pygtk.require("2.0")

        import gtk, threading
        gtk.gdk.threads_init()
        t = threading.Thread(target=gtk.main)
        t.daemon = True
        t.start()

        gtk.threads_enter()

        def expose(widget, event):
            import cairo
            import pango
            import pangocairo

            cr = widget.window.cairo_create()

            cr.set_source_rgb(0.30, 0.60, 0.02)
            cr.rectangle(event.area.x, event.area.y,
                         event.area.width, event.area.height)
            cr.fill()

            cr.set_source_rgb(1.0, 1.0, 1.0)
            cr.select_font_face("Calibri", cairo.FONT_SLANT_NORMAL, cairo.FONT_WEIGHT_NORMAL)
            cr.set_font_size(48)
            cr.move_to(20, 20)
            cr.show_text(self.get_current_file()["file"])

        self.window = gtk.Window(type=gtk.WINDOW_POPUP)
        self.window.set_keep_above(True)
        self.window.set_gravity(gtk.gdk.GRAVITY_NORTH_EAST)
        self.window.resize(960, 1080)
        self.window.move(960, 0)
        self.widget = gtk.DrawingArea()
        self.widget.connect("expose-event", expose)
        self.widget.show()
        self.window.add(self.widget)
        self.window.show()

        gtk.threads_leave()

    def play(self):
        import fcntl, os, os.path, re, subprocess, threading, time

        self.current_file_position = -1
        for file in self.playlist:
            path = os.path.join(self.directory, self.current_file)

            if file["state"] in [self.PLAYLIST_CURRENT, self.PLAYLIST_SCHEDULED]:
                file["state"] = self.PLAYLIST_CURRENT
                start = int(time.time())

                # self.show_window()

                self.current_file = file["file"]
                mplayer = subprocess.Popen(["mplayer", path], stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
                fcntl.fcntl(mplayer.stdout.fileno(), fcntl.F_SETFL, os.O_NONBLOCK)
                while mplayer.poll() == None:
                    try:
                        out = mplayer.stdout.read()
                    except IOError:
                        out = ""

                    m_pos = re.search("^A:([0-9. ]+)", out)
                    if m_pos:
                        self.current_file_position = float(m_pos.group(m_pos.lastindex))
                    time.sleep(0.1)

                end = int(time.time())
                file["state"] = self.PLAYLIST_INACTIVE

                #print path, start, end
                #threading.Thread(target=lambda: self.submit_to_timeline(path, self.ctime(path), start, end)).start()

    def ctime(self, path):
        import os
        return int(os.stat(path).st_mtime)

    def submit_to_timeline(self, filename, download, start, end):
        import glob, math, os, os.path, PIL, PIL.ImageStat, re, subprocess, tempfile

        title = os.path.basename(filename)

        i = 1
        length = self.get_file_length(filename)
        for ss in range(length / 5 + 1, length, length / 5 + 1):
            tmp_dir = str(tempfile.mkdtemp())

            subprocess.call(["mplayer", "-ss", str(ss), "-nosound", "-vc", ",", "-vo", "jpeg:outdir=" + tmp_dir, "-frames", "50", filename])

            max_brightness = -1
            max_brightness_image = None
            for image in glob.glob(os.path.join(tmp_dir, "0000*.jpg")):
                r, g, b = PIL.ImageStat.Stat(PIL.Image.open(image)).mean
                brightness = math.sqrt(0.241 * (r ** 2) + 0.691 * (g ** 2) + 0.068 * (b ** 2))
                if brightness > max_brightness:
                    max_brightness = brightness
                    max_brightness_image = image

            subprocess.call(["scp", max_brightness_image, "themylogin@192.168.0.1:/home/themylogin/www/thelogin.ru/data/movies/\"%(title)s.%(i)d.jpg\"" % {
                "title" : title,
                "i"     : i,
            }])

            for image in glob.glob(os.path.join(tmp_dir, "0000*.jpg")):
                os.unlink(image)

            i += 1

        #
        import simplejson
        from datetime import datetime
        from sqlalchemy import create_engine
        from sqlalchemy.orm import sessionmaker, scoped_session

        session_factory = scoped_session(sessionmaker(bind=create_engine('mysql://theMplayerShell:theMplayerShell@192.168.0.1/themylogin_thelogin?charset=utf8'), autocommit=True))
        session = session_factory()

        session.execute("""
            INSERT INTO thelogin_microblog
            (source, source_id, datetime, data)
            VALUES
            (:source, :source_id, :datetime, :data)
        """, params={
            "source"    : "movies",
            "source_id" : end,
            "datetime"  : datetime.fromtimestamp(end).strftime("%Y-%m-%d %H:%M:%S"),
            "data"      : simplejson.dumps({ "title" : title, "download" : download, "start" : start })
        })

    def get_current_file(self):
        for file in self.playlist:
            if file["state"] == self.PLAYLIST_CURRENT:
                return file

if __name__ == "__main__":
    import sys
    MPlayerShell(sys.argv[1], True)
