# Version 0.1

.PHONY: all tasks clean
.SECONDEXPANSION:
.SECONDARY:

ifneq 'yes' '$(VERBOSE)'
hidecmd := @
endif
# The variable SILENT controls additional messages

CPPFLAGS += -Wall -Wextra -Werror -Wno-missing-field-initializers -Werror=vla -pthread
CXXFLAGS += -g

system   := $(shell uname)

ifneq 'MINGW' '$(patsubst MINGW%,MINGW,$(system))'
CPPFLAGS += -std=c++17
else
CPPFLAGS += -std=gnu++17
endif

ifeq 'Darwin' '$(system)'
TIMEOUT_CMD := gtimeout
else
TIMEOUT_CMD := timeout
endif

tasks := $(filter-out out Makefile,$(wildcard *))

task_sources        = $(wildcard $(1)/*.cpp)
task_headers        = $(wildcard $(1)/*.h) $(wildcard $(1)/*.hpp) $(wildcard $(1)/*.hxx)
task_common_sources = $(if $(wildcard $(1)/common),$(wildcard $(1)/common/*.cpp))
task_common_headers = $(if $(wildcard $(1)/common),$(wildcard $(1)/common/*.h) $(wildcard $(1)/common/*.hpp) $(wildcard $(1)/common/*.hxx))

task_objects        = $(patsubst %.cpp,out/%.o,$(call task_sources,$(1)) $(call task_common_sources,$(1)))
task_header_checks  = $(addprefix out/,$(addsuffix .header,$(call task_headers,$(1)) $(call task_common_headers,$(1))))

objects            := $(sort $(foreach task,$(tasks),$(call task_objects,$(task))))
test_objects       := $(sort $(foreach task,$(tasks),$(call task_test_objects,$(task))))
header_checks      := $(sort $(foreach task,$(tasks),$(call task_header_checks,$(task))))

common_include     = $(if $(wildcard $(1)/common),-I$(1)/common -I$(1)/common/include)

all:
	$(addprefix build-,$(tasks))

tasks:
	@echo $(tasks)

$(addprefix run-,$(tasks)): run-%: out/%/task
	@$(FAULT_INJECTION_CONFIG) $(if $(TIMEOUT),$(TIMEOUT_CMD) --signal=KILL $(TIMEOUT)s )$(if $(VALGRIND),valgrind $(VALGRIND) )$< $(ARGS)

clean:
	rm -rf out

$(addprefix build-,$(tasks)): build-%: out/%/task

out/%/task: $$(call task_objects,%) $$(call task_header_checks,%) | $$(@D)/.dir
	$(if $(SILENT),,@echo [LINK] $(patsubst out/%/task,%,$@))
	$(hidecmd)$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) -o $@ $(filter-out %.header,$^)

$(objects): out/%.o: %.cpp | $$(@D)/.dir
	$(if $(SILENT),,@echo [C++ ] $<)
	$(hidecmd)$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MMD -MP -c $(call common_include,$<) -o $@ $<

$(header_checks): out/%.header: % | $$(@D)/.dir
	$(if $(SILENT),,@echo [HDR ] $<)
	$(hidecmd)$(CXX) $(CPPFLAGS) $(CXXFLAGS) -Wno-unused-const-variable -c $(call common_include,$<) -fsyntax-only $<
	@touch $@

%/.dir:
	@mkdir -p $(@D) && touch $@

include $(wildcard $(patsubst %.o,%.d,$(objects)))
