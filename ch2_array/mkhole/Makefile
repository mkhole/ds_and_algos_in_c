
APPS := triangle_matrix padd poly_matrix
OBJDIR := build

triangle_matrix_SRCS := triangle_matrix.c
padd_SRCS := padd.c
poly_matrix_SRCS := poly_matrix.c

ifndef OBJDIR
 $(error "OBJDIR is not defined. Aborting")
endif

ifndef APPS
 $(error "APPS is not defined. Aborting")
endif

define EXPAND_VAR 
 $(1)_OBJS :=  $$(patsubst %.c,$(OBJDIR)/%.o,$$($(1)_SRCS))
 OBJS += $$($(1)_OBJS)
 EXES += $$(patsubst %,$(OBJDIR)/%,$(1))
endef

$(foreach app,$(APPS),$(eval $(call EXPAND_VAR,$(app))))

.PHONY : all clean

CFLAGS  += -Wall -g
LDFLAGS +=

all: $(OBJDIR) $(EXES)
	@echo "Finish!"

-include $(OBJDIR)/*.d

$(OBJDIR):
	mkdir -p $@

$(EXES): $(OBJS)
	$(CC) $($(@F)_OBJS) $(LDFLAGS) -o $@

$(OBJDIR)/%.o: %.c
	$(CC) -c $(CFLAGS) -MMD -MT$(@) $< -o $@

clean:
	$(RM) -rf $(OBJDIR)
