# ==========================================
# Makefile pour Sous-Répertoires
# ==========================================

CC = gcc
CFLAGS = -Wall -Wextra -g -O2 -Iinclude
LIBS = -lm

# Dossiers
SRCDIR = src
APPDIR = apps
INCDIR = include
OBJDIR = obj

# Trouve tous les .c dans src/ et ses sous-dossiers
UTILS_SRCS = $(shell find $(SRCDIR) -name "*.c")

# Transforme src/crypto/utils.c -> obj/utils.o
# On utilise 'notdir' pour ne pas recréer l'arborescence dans obj/
UTILS_OBJS = $(patsubst %.c, $(OBJDIR)/%.o, $(notdir $(UTILS_SRCS)))

# Indique à Make où chercher les fichiers sources (.c)
VPATH = $(shell find $(SRCDIR) -type d)

# Détection des programmes
APP_SRCS = $(wildcard $(APPDIR)/*.c)
TARGETS = $(patsubst $(APPDIR)/%.c, %, $(APP_SRCS))

all: $(OBJDIR) $(TARGETS)

$(OBJDIR):
	mkdir -p $(OBJDIR)

# Compilation des modules (grâce à VPATH, il trouve les .c)
$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Liaison finale
%: $(APPDIR)/%.c $(UTILS_OBJS)
	$(CC) $(CFLAGS) $< $(UTILS_OBJS) -o $@ $(LIBS)
	@echo "--- Exécutable $@ créé ---"

clean:
	rm -rf $(OBJDIR) $(TARGETS)

.PHONY: all clean
