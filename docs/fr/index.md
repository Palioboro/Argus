# cargs

![CI/CD Pipeline](https://github.com/lucocozz/cargs/actions/workflows/ci.yml/badge.svg)
![CodeQL Analysis](https://github.com/lucocozz/cargs/actions/workflows/codeql.yml/badge.svg)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

> Bibliothèque C moderne pour l'analyse des arguments de ligne de commande avec une API élégante basée sur des macros.

**cargs** est une bibliothèque C puissante pour gérer les arguments de ligne de commande, conçue pour être à la fois simple à utiliser et suffisamment flexible pour les scénarios d'utilisation avancés.

## ✨ Fonctionnalités

- 📋 **Génération d'aide** : affichage automatique et formaté de l'aide et de l'utilisation
- 🔄 **Options typées** : booléens, entiers, chaînes de caractères, flottants, tableaux, mappages
- 🎨 **Analyse de format flexible** : prend en charge plusieurs formats d'options (--option=valeur, --option valeur, -ovaleur, etc.)
- 🌳 **Sous-commandes** : prise en charge des commandes imbriquées de style Git/Docker
- ⚠️ **Rapports d'erreurs clairs** : messages d'erreur détaillés et conviviaux pour les options ou valeurs invalides
- ✨ **Design élégant** : définition des options avec des macros concises et expressives
- 🔍 **Validateurs intégrés** : validateurs de plage, de choix et d'expressions régulières avec des ensembles prédéfinis complets
- 📦 **Regroupement organisé des options** : regroupement visuel des options associées dans l'affichage d'aide
- 🔗 **Relations entre options** : définition de dépendances et de conflits entre options
- 🔧 **Validation de structure** : vérification complète de la structure des options lors de l'initialisation pour éviter les erreurs d'exécution
- 🌐 **Variables d'environnement** : configuration ENV automatique
- 🚀 **Efficacité mémoire** : minimise les allocations sur le tas pour de meilleures performances et fiabilité
- 🧰 **Personnalisation facile des options** : créez vos propres types d'options et gestionnaires
- 🛡️ **Pipeline de validation personnalisé** : concevez vos propres validateurs avec un pré/post-traitement flexible

## Exemple rapide

```c
#include "cargs.h"
#include <stdio.h>

// Définition des options
CARGS_OPTIONS(
    options,
    HELP_OPTION(FLAGS(FLAG_EXIT)),
    VERSION_OPTION(FLAGS(FLAG_EXIT)),
    OPTION_FLAG('v', "verbose", "Activer la sortie verbeuse"),
    OPTION_STRING('o', "output", "Fichier de sortie", DEFAULT("output.txt")),
    OPTION_INT('p', "port", "Numéro de port", RANGE(1, 65535), DEFAULT(8080)),
    POSITIONAL_STRING("input", "Fichier d'entrée")
)

int main(int argc, char **argv)
{
    // Initialiser cargs
    cargs_t cargs = cargs_init(options, "my_program", "1.0.0");
    cargs.description = "Démonstrateur de cargs";

    // Analyser les arguments
    if (cargs_parse(&cargs, argc, argv) != CARGS_SUCCESS) {
        return 1;
    }

    // Accéder aux valeurs analysées
    const char *input = cargs_get(cargs, "input").as_string;
    const char *output = cargs_get(cargs, "output").as_string;
    int port = cargs_get(cargs, "port").as_int;
    bool verbose = cargs_get(cargs, "verbose").as_bool;

    printf("Configuration :\n");
    printf("  Entrée : %s\n", input);
    printf("  Sortie : %s\n", output);
    printf("  Port : %d\n", port);
    printf("  Verbose : %s\n", verbose ? "oui" : "non");

    // Libérer les ressources
    cargs_free(&cargs);
    return 0;
}
```

## 🚀 Démarrage rapide

- [Installation](guide/installation.md) - Comment installer la bibliothèque cargs
- [Démarrage rapide](guide/quickstart.md) - Créez votre première application avec cargs
- [Exemples](examples/basic.md) - Explorez des exemples d'utilisation

## 📚 Documentation

La documentation est organisée comme suit :

- **[Guide de l'utilisateur](guide/installation.md)** - Instructions détaillées pour utiliser cargs
- **[Référence API](api/overview.md)** - Référence complète de l'API cargs
- **[Exemples](examples/basic.md)** - Exemples de code pratiques
- **[Fonctionnalités avancées](advanced/custom-handlers.md)** - Utilisation des fonctionnalités avancées
