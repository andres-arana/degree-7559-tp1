.PHONY: all run doc doc-preview doc-spell srcdoc srcdoc-preview clean export

EXECS=audit carrousel carrouselq cashier cashierq childinc director exitq spawner
LIBS=util raii syscalls

EXECS_PATHS=$(addprefix build/exec/, $(EXECS))

CC=g++
CCFLAGS=-std=c++11 -Wall -Wextra -g -MP -MMD
INCLUDES=-I src -I libs

###############################################################################
# Helpers and administrative tasks
###############################################################################
all: $(EXECS_PATHS)

run: all
	build/exec/director -l 0 -p 30 -d 5 -c 5

doc: build/doc/informe.pdf

doc-preview: doc
	evince build/doc/informe.pdf &

doc-spell: docs/informe.tex
	aspell -t check docs/informe.tex -d es

srcdoc: | build/srcdoc
	doxygen doxyfile

srcdoc-preview: srcdoc
	firefox build/srcdoc/html/index.html

clean:
	rm -rf build
	rm -f concucalesita.log

export: all doc
	# TODO: Complete the export task

###############################################################################
# Executable building
###############################################################################
build:
	mkdir $@

build/objs: | build
	mkdir $@

build/exec: | build
	mkdir $@

define GENERATE_COMPILATION_RULES

$(1)_objs=$$(addsuffix .o,$$(basename $$(subst src/,build/objs/,$$(wildcard src/$(1)/*.cpp))))

$(1)_deps=$$(wildcard build/objs/$(1)/*.d)

-include $$($(1)_deps)

build/objs/$(1): | build/objs
	mkdir $$@

build/objs/$(1)/%.o: src/$(1)/%.cpp | build/objs/$(1)
	$$(CC) $$(CCFLAGS) $$(INCLUDES) -c $$< -o $$@

endef

define GENERATE_LINK_RUNLES

build/exec/$(1): $$($(1)_objs) $$(util_objs) $$(raii_objs) $$(syscalls_objs) | build/exec
	$$(CC) $$^ -o $$@

endef

$(foreach compilable,$(EXECS),$(eval $(call GENERATE_COMPILATION_RULES,$(compilable))))
$(foreach compilable,$(LIBS),$(eval $(call GENERATE_COMPILATION_RULES,$(compilable))))
$(foreach executable,$(EXECS),$(eval $(call GENERATE_LINK_RUNLES,$(executable))))

###############################################################################
# Documentation building
###############################################################################
build/srcdoc: | build
	mkdir build/srcdoc

build/doc: | build
	mkdir build/doc

build/doc/informe.pdf: docs/informe.tex | build/doc
	pdflatex --output-directory build/doc docs/informe.tex
	pdflatex --output-directory build/doc docs/informe.tex
	pdflatex --output-directory build/doc docs/informe.tex

