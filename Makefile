SHELL = /bin/sh


ROOT  = /
DEST  = $(ROOT)/usr
qmake = $(QTDIR)/bin/qmake
lrelease = $(QTDIR)/bin/lrelease
#DEST  = /usr/local
BINPATH = $(DEST)/bin
INCPATH = $(DEST)/include/hde2
LIBPATH = $(DEST)/lib
MANPATH = $(DEST)/share/man
SHAREPATH= $(DEST)/share/hde2
XDGPATH  = $(ROOT)/etc/xdg
DATAPATH = $(DEST)/share
STYLESDIR= $(ROOT)/$(QTDIR)/plugins/styles
DESIGDIR= $(ROOT)/$(QTDIR)/plugins/designer

DVERSION = 2.0.3
LVERSION = 2.0.3

all: config
	cd libhde ; LVERSION=$(LVERSION) $(qmake); $(lrelease) libhde.pro; \
	  $(MAKE)
	cd libhde ; $(qmake) hdeStyle.pro ;  $(MAKE); $(qmake)
	cd libhde/hdeplugins ; $(qmake); $(MAKE); $(qmake)
	cd hde   ; $(qmake); $(lrelease) hde.pro; $(MAKE)
#	cd extra/biff   ; $(lrelease) biff.pro; $(qmake); $(MAKE)
	cd extra/hrun   ; $(qmake); $(lrelease) hrun.pro; $(MAKE)
	cd extra/hDisplay   ; $(qmake); $(lrelease) hDisplay.pro; $(MAKE)
	cd extra/hDateTime  ; $(qmake); $(lrelease) hDateTime.pro; $(MAKE)
#	cd extra/hadditem   ; $(lrelease) hadditem.pro; $(qmake); $(MAKE)
	cd extra/deskitem   ; $(qmake); $(lrelease) deskitem.pro; $(MAKE)
	cd extra/hxkb   ; $(qmake); $(lrelease) hxkb.pro; $(qmake); $(MAKE)

config: Makefile
	cd files ; \
	sed -e s%@BASEDIR@%$(BINPATH)%g < defaults.in > defaults1 && \
	sed -e s%@SHAREDIR@%$(SHAREPATH)%g < defaults1 > defaults && \
	rm -rf defaults1

	cd include ; \
	(echo "#define HDEPATH \"$(DEST)\"" ; \
	echo "#define INCPATH \"$(INCPATH)\"" ; \
	echo "#define LIBPATH \"$(LIBPATH)\"" ; \
	echo "#define CONFDIR \"$(SHAREPATH)\"" ;\
	echo "#define DVERSION \"$(LVERSION)\"") > lhdeconf.h;
	cd hde ; \
	(echo "#define CONFDIR \"$(SHAREPATH)\"" ; \
	echo "#define DVERSION \"$(DVERSION)\"") > conf.h ;
	
	(echo "export LVERSION=$(LVERSION)";\
	 echo "export DVERSION=$(DVERSION)") > config;
	touch config;

	(echo "#/sbin/bash" ; \
	 echo "mkdir -p ~/.config/hde2" ; \
	 echo "cd $(SHAREPATH)" ;\
	 echo "cp defaults ~/.config/hde2" ;\
	 echo "cp appdefaults ~/.config/hde2" ;\
	 echo "cp -r userfiles/* ~/.config/hde2") > hdeinst 

distclean:
	cd libhde ; LVERSION=$(LVERSION) $(qmake); libhde.pro; \
	  $(MAKE) distclean
	cd libhde ; $(qmake) hdeStyle.pro ;  $(MAKE) distclean; $(qmake)
	cd libhde/hdeplugins ; $(qmake);  $(MAKE) distclean
	cd hde ; $(qmake); $(MAKE) distclean
#	cd extra/biff ; $(MAKE) distclean
	cd extra/hrun ;$(qmake); $(MAKE) distclean
	cd extra/hDisplay; $(qmake) ; $(MAKE) distclean
	cd extra/hDateTime; $(qmake) ; $(MAKE) distclean
#	cd extra/hadditem; $(qmake)   ; $(MAKE) distclean
	cd extra/deskitem; $(qmake)   ; $(MAKE) distclean
	cd extra/hxkb; $(qmake)   ; $(MAKE) distclean
	cd debian; rm -f hde_* libhde_*
	rm -f config files/defaults
	rm -f *~ core config hdeinst
	rm -f lib/libhde*
	rm -f libhde/*.so
	rm -f include/*~

clean:
	cd libhde ; LVERSION=$(LVERSION) $(qmake); libhde.pro; $(MAKE) clean
	cd libhde ; $(qmake) hdeStyle.pro ;  $(MAKE) clean; $(qmake)
	cd libhde/hdeplugins ; $(qmake);  $(MAKE) clean
	cd hde ;$(qmake); $(MAKE) clean
#	cd extra/biff ; $(MAKE) clean
	cd extra/hrun ;$(qmake); $(MAKE) clean
	cd extra/hDisplay ;$(qmake); $(MAKE) clean
	cd extra/hDateTime ;$(qmake); $(MAKE) clean
#	cd extra/hadditem   ; $(MAKE) clean
	cd extra/deskitem   ;$(qmake); $(MAKE) clean
	cd extra/hxkb   ; $(qmake); $(MAKE) clean
	rm -f config files/defaults
	rm -f *~ core config hdeinst
	rm -f include/*~

dist:	distclean
	find -exec touch {} \; ; \
	d=hde-$(DVERSION) ; \
	cd .. ; \
	rm -f $${d}.tar.gz ; \
	ln -s hde $${d} ; \
	tar cvjhf $${d}.tar.bz2 $${d} ; \
	rm $${d}

install: all
	mkdir -p $(SHAREPATH)
	mkdir -p $(INCPATH)
	mkdir -p $(BINPATH)
	mkdir -p $(LIBPATH)
	mkdir -p $(STYLESDIR)
	mkdir -p $(XDGPATH)
	cp include/*.h $(INCPATH)
	cd hde    ; install -s ./hde $(BINPATH)/hde
#	cd extra/biff   ; install -s ./biff $(BINPATH)/biff
	cd extra/hrun   ; install -s ./hrun $(BINPATH)/hrun
	cd extra/hDisplay; install -s ./hDisplay2 $(BINPATH)/hDisplay2
	cd extra/hDateTime; install -s ./hDateTime $(BINPATH)/hDateTime
#	cd extra/hadditem ; install -s ./hadditem $(BINPATH)/hadditem
	cd extra/deskitem ; install -s ./deskitem $(BINPATH)/deskitem
	cd extra/hxkb ; install -s ./hxkb $(BINPATH)/hxkb
	rm -rf $(LIBPATH)/libhde2.so*
	cd lib;cp -aR ./libhde2.so* $(LIBPATH)/
	cd libhde; install -s ./libhdeStyle.so $(STYLESDIR)
	cd libhde/hdeplugins; install -s ./libhdeplugins.so $(DESIGDIR)
	cp ./README $(SHAREPATH)/README
	install -c ./hde.1 $(MANPATH)/man1/hde2.1
	cp hdeinst $(BINPATH)/hde2inst
	chmod 755 $(BINPATH)/hde2inst
#	cd $(LIBPATH); ln -sf libhde2.so.$(LVERSION) libhde2.so.0.9; \
#	ln -sf libhde2.so.0.9 libhde2.so.0; ln -sf libhde2.so.0 libhde2.so
#	cd files && cp -r * $(SHAREPATH) 
	cd files && cp -r defaults appdefaults $(SHAREPATH)
	cd files && cp -r userfiles lng images $(SHAREPATH)
	cd files && cp -r applnk $(SHAREPATH)
	cd files && cp -r *Theme* $(SHAREPATH)
	cd files && cp -r xdg/* $(XDGPATH)/
	cd files && cp -r desktop-directories $(DATAPATH)
	cd files && cp -r applications $(DATAPATH)
	cd files && cp -r xsessions $(DATAPATH)

	find $(DATAPATH) -type d -name CVS | xargs rm -rf
	find $(XDGPATH) -type d -name CVS | xargs rm -rf
	find $(DATAPATH) -type d -name .svn | xargs rm -rf
	find $(XDGPATH) -type d -name .svn | xargs rm -rf

