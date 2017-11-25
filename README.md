# 42sh project

Le projet 42sh comprends :

* Une édition de la ligne de commande à l’aide de la bibliothèque termcaps.
* Editer la ligne à l’endroit où se trouve le curseur.
* Déplacer le curseur vers la gauche et vers la droite pour pouvoir éditer la ligne àun endroit précis. Les nouveaux caractères doivent bien entendu s’insérer entre les
caractères existants de la même manière que dans un shell ordinaire.
* Utiliser les fl`ches du haut et du bas pour naviguer dans l’historique des commandes
que l’on pourra alors éditer si le coeur nous en dit (la ligne, pas l’historique, hein).
* Couper, copier et/ou coller tout ou partie d’une ligne avec la séquence de touches
qui vous plaira.
* Se déplacer par "mot" vers la gauche et vers la droite avec ctrl+LEFT et ctrl+RIGHT
ou toute autre combinaison de touche raisonnable.
* Aller directement au début et à la fin d’une ligne avec home et end.
* Ecrire ET éditer une commande sur plusieurs lignes. Dans ce cas, on apprecierait
que ctrl+UP et ctrl+DOWN permettent de passer d’une ligne à l’autre de la
commande en restant sur la même colonne ou la colonne la plus appropriée sinon.
* Les fonctionnalités des combinaisons de touches ctrl+D et ctrl+C dans l’édition
de la ligne et l’éxecution d’un processus.
* Une acquisition de ligne minimale.
* Affichage d’un prompt.
* lecture de la ligne de commande, sans édition de ligne.
* Gestion correcte des espaces et des tabulations.
* Les builtins suivantes avec toutes leurs options si elles en ont (au strict minimum
les options dictées par le standard POSIX) :
* cd
* echo
* exit
* env
* setenv
* unsetenv
* Exécution de commandes simples avec leurs paramètres et gestion du PATH.
* Gestion des erreurs et de la valeur de retour des commandes
* Les opérateurs de redirection suivants : ">", ">>", "<" et "|".
* Les aggrégations de descripteurs de fichiers, par exemple pour fermer la sortie
d’erreur : "<&", ">&"
* Les opérateurs logiques "&&" et "||".
* Le séparateur ";".
* Les inhibiteurs """ (double quote), "’" (simple quote) et "\" (backslash).
* Les redirections avancées : l’aggrégation des sorties de fichier et le heredoc "<<".
* les variables locales et les builtin unset et export.
* L’historique des commandes et les builtins history et "!" avec toutes leurs options
si elles en ont.
* Edition de ligne telle que demandée dans le ft_sh3.
* Les descripteurs de fichiers et la builtin read avec toutes ses options.
* Complétion dynamique.
* Le Job control et les builtins jobs, fg et bg, et l’operateur "&".

### Command line:

*	`M-C` copy
*	`M-X` cut
*	`M-V` paste
*	`ctrl-R` frontward history search
*	`ctrl-N` frontward history search
*	`Home`: Append the line
*	`End`: End the line
*	`M-(left/right)arrow` move through words
*	`M-(up/down)arrow` move through lines
*	`(up/down)arrow` go backward/frontward through historty
*	`Ctrl-L` clear screen
*	`ctrl-U` clear command
