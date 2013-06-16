# A general makefile which invokes all makefiles in every utility directory.

MKDIR = ./utilities/mkdir
RMDIR = ./utilities/rmdir
CHMOD = ./utilities/chmod
TEE = ./utilities/tee
CHOWN = ./utilities/chown
TAIL = ./utilities/tail

TOOLS = $(MKDIR) $(RMDIR) $(CHMOD) $(TEE) $(CHOWN) $(TAIL)

.PHONY: all
all: $(TOOLS)

.PHONY: $(MKDIR)
$(MKDIR):
	@$(MAKE) -C $@

.PHONY: $(RMDIR)
$(RMDIR):
	@$(MAKE) -C $@

.PHONY: $(CHMOD)
$(CHMOD): 
	@$(MAKE) -C $@

.PHONY: $(TEE)
$(TEE):
	@$(MAKE) -C $@
	
.PHONY: $(PRINTENV)
$(PRINTENV):
	@$(MAKE) -C $@

.PHONY: $(CHOWN)
$(CHOWN):
	@$(MAKE) -C $@
	
.PHONY: $(TAIL)
$(TAIL):
	@$(MAKE) -C $@

.PHONY: install
install:
	mkdir LinuxUtilities
	mv ./utilities/mkdir/mkdir LinuxUtilities
	mv ./utilities/rmdir/rmdir LinuxUtilities
	mv ./utilities/chmod/chmod LinuxUtilities
	mv ./utilities/tee/tee LinuxUtilities
	mv ./utilities/chown/chown LinuxUtilities
	mv ./utilities/tail/tail LinuxUtilities
	
.PHONY: clean
clean:
	rm -f ./utilities/mkdir/*.o
	rm -f ./utilities/rmdir/*.o
	rm -f ./utilities/chmod/*.o
	rm -f ./utilities/tee/*.o
	rm -f ./utilities/chown/*.o
	rm -f ./utilities/tail/*.o
	rm -rf ./LinuxUtilities
