.PHONY: clean doc-preview doc-spell export all doc

EXECS=audit carrousel cashier child director spawner
LIBS=util

EXECS_PATHS=$(addprefix build/exec/, $(EXECS))
LIBS_PATHS=$(addprefix build/libs/, $(LIBS))

CC=g++
CCFLAGS=-std=c++11 -Wall -Wextra -g -MP -MMD
INCLUDES=-I src

###############################################################################
# Helpers and administrative tasks
###############################################################################
all: $(EXECS_PATHS)

doc: build/doc/informe.pdf

doc-preview: doc
	evince build/doc/informe.pdf &

doc-spell: docs/informe.tex
	aspell -t check docs/informe.tex -d es

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

build/exec/$(1): $$($(1)_objs) $$(util_objs) | build/exec
	$$(CC) $$^ -o $$@

endef

$(foreach compilable,$(EXECS),$(eval $(call GENERATE_COMPILATION_RULES,$(compilable))))
$(foreach compilable,$(LIBS),$(eval $(call GENERATE_COMPILATION_RULES,$(compilable))))
$(foreach executable,$(EXECS),$(eval $(call GENERATE_LINK_RUNLES,$(executable))))

###############################################################################
# Documentation building
###############################################################################
build/doc: | build
	mkdir build/doc

build/doc/informe.pdf: docs/informe.tex | build/doc
	pdflatex --output-directory build/doc docs/informe.tex
	pdflatex --output-directory build/doc docs/informe.tex
	pdflatex --output-directory build/doc docs/informe.tex

