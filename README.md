dwm - dynamic window manager
============================
dwm is an extremely fast, small, and dynamic window manager for X.


Requirements
------------
In order to build dwm you need the Xlib header files.


Installation
------------
Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install


Running dwm
-----------
Add the following line to your .xinitrc to start dwm using startx:

    exec dwm

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec dwm

(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:

    while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
    do
    	sleep 1
    done &
    exec dwm


Configuration
-------------
The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.

# Personal build
The following patches have been applied:
```
dwm-alpha-20201019-61bb8b2.diff         dwm-fsignal-6.2.diff
dwm-alwayscenter-20200625-f04cac6.diff  dwm-restartsig-20180523-6.2.diff
dwm-autostart-20210120-cb3f58a.diff     dwm-statuscolors-20181008-b69c870.diff
dwm-bar-height-6.2.diff                 dwm-uselessgap-20200719-bb2e722.diff
dwm-colorbar-6.2.diff                   dwm-xresources-20210827-138b405.diff
dwm-actualfullscreen-20211013-cb3f58a.diff
```

## Instrunctions
1. `autostart.sh` is to be placed in `~/.local/share/dwm/`.
2. `sxhkdrc` is to be placed in `~/.config/sxhkd/`. (`sxhkd` must to be installed).
3. Install [`dwmblocks`](https://github.com/mrishu/dwmblocks).
4. Install [`dmenu`](https://github.com/mrishu/dmenu).
5. _OPTIONAL_: Copy the contents of `dwm.xresources` to `~/.Xresources` file and run
```
xrdb -merge ~/.Xresources
```
6. Install _Feather_ font (available in `dotfiles` repo in `fonts` directory), JetBrainsMono Nerd Font and 
JetBrains Mono.

## Drawbacks in Personal build
1. `baralpha` variable which adjusts transparency of bar isn't available through
Xresources and must be adjusted in `config.def.h` itself.

2. On line 752 of `dwm.c`, the padding will need to be adjusted manually, 
(only once after the number of active dwmblocks modules has been decided).
