# Compiler
CXX = g++

# Options de compilation
CXXFLAGS = -Wall -Iinclude

# Bibliothèques
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -ltinyxml2

# Fichiers source
SRCDIR = ../src
SRCS = $(wildcard $(SRCDIR)/*.cpp)

# Fichiers d'en-tête
INCDIR = ../include

# Exécutable
EXEC = NoName

# Règle de compilation
$(EXEC): $(SRCS)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) $^ -o $@ $(LIBS)

# Règle pour nettoyer les fichiers temporaires et l'exécutable
clean:
	rm -f $(EXEC)

# Régles mrproper
mrproper: clean
	rm -f $(EXEC)

# Règle pour lancer avec valgrind
valgrind: $(EXEC)
	valgrind --leak-check=full ./$(EXEC)

# Règle pour compter les lignes de code
count:
	wc -l $(SRCS) $(INCDIR)/*.h

# Commande pour générer une version de release et créer un zip
release:
	# Créer le répertoire de destination
	mkdir -p release
	mkdir -p release/game
	# Copier l'exécutable dans le répertoire de destination
	cp echoes release/game/echoes
	# Copier le répertoire de données dans le répertoire de destination
	cp -r ../data release/
	# Créer le fichier zip
	zip -r release.zip release/
	# Nettoyer les fichiers temporaires
	rm -rf release

# Installation des dépendances avec pacman
install:
	sudo pacman -S sfml tinyxml2 sfml

