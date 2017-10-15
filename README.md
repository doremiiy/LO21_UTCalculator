# LO21_UTCalculator

## Introduction

Lors de ce projet, nous avons à réaliser une calculette scientifique permettant d’effectuer des calculs en manipulant 
des **Littérales**, des **Variables** et des **Programmes**, en utilisant la notation polonaise inverse 
(**RPN** : **R**everse **P**olish **N**otation).
Cette notation permet d’écrire une formule arithmétique sans ambiguïté et sans utiliser de parenthèses.

La RPN impose également l’utilisation d’une pile pour stocker les résultats de la formule.

## Architecture de l’application

Une étape primordiale dans la réalisation de ce projet a été de réfléchir à une architec- ture satisfaisante permettant 
à la fois de répondre à toutes les problématiques du sujet, et d’offrir une certaine modularité dans notre application.

### Modélisation conceptuelle

Nous avons donc pu discerner trois grandes familles de classes qui vont composer l’ensemble de l’application :
- La gestion des littérales
- La gestion des opérateurs
- La gestion de la pile

#### La gestion des littérales

![litterales_uml](https://raw.githubusercontent.com/remid0/LO21_UTCalculator/master/UML/litterales.png)

##### Justifications

L’application doit pouvoir gérer plusieurs types de littérales. C’est pourquoi nous avons choisis d’utiliser le 
design pattern **Factory Method**, afin d’instancier des objets dont le type est dérivé d’un type abstrait 
(ici le type **Littérale**). Ce design pattern fournit une interface générale pour la création d’un objet tout 
en déléguant aux sous-classes le soin de choisir la classe à instancier.

La classe **FabriqueLitterale** implémente le design pattern **Singleton**, ce qui permet d’assurer l’unicité de 
l’instance de cette classe.

Il existe une relation de composition entre la classe abstraite **LitteraleNumeric** et **Complexe**. En effet, 
un complexe est composé d’une partie réelle et d’une partie imaginaire qui peuvent toutes deux être soit un entier, 
un réel ou un rationnel.

Nous aurions pu également faire une relation de composition entre les classes **Entier** et **Rationnel** car il est 
précisé qu’un rationnel possède un numérateur et un dénominateur qui sont tous deux entiers. Cependant, nous avons 
estimé qu’il était plus simple d’utiliser le type integer pour ces deux attributs.

La même remarque s’applique pour les réels qui auraient pu être une composition de deux entiers représentant respectivement 
la partie entière et la partie décimale. Cependant, nous avons choisi, encore une fois pour des raisons de simplicité, 
d’utiliser un unique attribut de type double.

#### La gestion des opérateurs

![operateurs_uml](https://raw.githubusercontent.com/remid0/LO21_UTCalculator/master/UML/operateurs.png)

#####Justifications

Sur les littérales et sur la pile peuvent s’appliquer différents types d’opérateurs. C’est pourquoi, comme pour les 
littérales, nous avons choisi d’utiliser le design pattern **Factory Method** pour instancier des objets dérivant du 
type abstrait **Operateur**.

De même, la classe **FabriqueOperateur** implémente le design pattern **Singleton**, ne permettant qu’une seule instance 
de la classe.
Nous avons différencié les opérateurs selon trois classes : les opérateurs binaires, les opérateurs unaires et 
les opérateurs qui agissent sur la pile. Ainsi, nous avons créé trois classes abstraites implémentant une interface 
générale pour chacun des types d’opéra- teurs. Chaque opérateur est donc représenté par une classe concrète qui hérite 
d’une de ces trois classes.

#### La gestion de la pile

![pile_uml](https://raw.githubusercontent.com/remid0/LO21_UTCalculator/master/UML/pile.png)

#####Justifications

Un objet de la classe **Item** encapsule un objet de la classe **Litterale**, et la classe **Pile** agrège des objets **Item**.
Les classes **Memento** et **CareTaker** permettent d’assurer la sauvegarde de l’état de la pile à chaque fois que l’état 
de celle-ci est modifié. La classe **Memento** contient des objets de la classe **Item** correspondant à un état de la pile 
à un moment donné. La classe **CareTaker** permet elle de sauvegarder ces états afin de pouvoir y faire appel avec les 
opérations *UNDO* et *REDO*.
La classe **Controleur** fait la liaison entre l’utilisateur et la pile. Elle implémente également le design pattern 
**Singelton**.

#### Application

![application_uml](https://raw.githubusercontent.com/remid0/LO21_UTCalculator/master/UML/application.png)

Un objet de la classe **Item** encapsule un objet de la classe **Litterale**. On a donc unerelation de composition entre 
ces deux classes.

## Spécifications techniques

Afin de répartir plus facilement le travail et de centraliser notre code, nous avons travaillé avec l’outil **GitHub**.

Pour ce projet, nous avons également fait le choix d’utiliser l’outil **Qt Creator** permettant de créer relativement 
facilement une interface graphique pour la calculette. Enfin, nous utilisons certaines classes de la bibliothèque standard 
du C++ adaptées à Qt, telles que *QVector* ou *QHash*.

Pour la sauvegarde du contexte de la pile, des variables et des paramètres, 
nous avons fais le choix d’utiliser l’outil **QtXml** implémenté par **Qt Creator** et permettant aisément l’écriture et la 
lecture dans un fichier **XML**. En effet, étant donné le peu d’information à stocker, il nous a semblé inutile de travailler 
avec une base de données, ce qui aurait complexifié et alourdi notre application.

La gestion de toutes les exceptions se fait à travers une même classe **ComputerException** qui capte les messages d’erreur 
pour les renvoyer à l’utilisateur à travers une méthode **getInfo()**.

Notre fichier de sauvegarde se compose de la sorte :
```
<?xmlversion="1.0" encoding="ISO-8859-1"?>
<context>
    <pile>
        <litterale>2</litterale>
        <litterale>1</litterale>
    </pile>
    <variables>
        <var>B_6</var>
        <var>A_5</var>
    </variables>
    <programmes>
        <prog>C_[NEG1]</prog>
    </programmes>
    <parametres>
        <son>1</son>
        <clavier>0</clavier>
        <clavierComplet>1</clavierComplet>
        <opPile>0</opPile>
        <taillePile>5</taillePile>
    </parametres>
</context>
```

A chaque fois qu’un utilisateur ouvre l’application, la lecture du fichier de sauvegarde s’exécute pour récupérer les 
informations de la dernière session lors de la création de la fenêtre principale.

Lorsque l’utilisateur quitte l’application, le fichier est écrasé puis ré-écrit avec les informations présentes dans 
l’application.

Nous n’avons cependant pas eu le temps de réaliser la sauvegarde des différents paramètres de la pile. L’implémentation de 
cette fonctionnalité serait quasi-similaire aux autres éléments sauvegardés.

## Présentation de l’interface graphique

Notre interface se décompose en quatre onglets :
— Une vue principale de la pile
— Une vue pour les variables **littérales numériques** permettant également la modification, la suppression d’une variable 
et la suppression de l’ensemble des variables
— Une vue similaire pour les variables **programmes**. Cette vue permet également l’édition d’un programme préalablement 
enregistré, provoquant l’ouverture d’une fenêtre dédiée à cette tâche
— Une vue permettant la gestion de l’ensemble des paramètres de l’application

Sur la vue principale, l’utilisateur dispose d’une ligne de commande afin de taper les instructions à effectuer. Ces 
instructions sont gérées par la classe **Controleur**.

Dans un premier temps, le contrôleur extrayait une par une les instructions de la ligne de commande. Cependant, dès lors 
que l’utilisateur peut rentrer des programmes ou des expressions avec des espaces, cette méthode ne fonctionnait plus. 
Nous avons donc choisi de *parser* la ligne de commande au préalable afin d’en vérifier la validité d’une part, et d’en 
extraire dans un vecteur chaque instruction à effectuer (programmes, expressions et littérales) d’autre part.

De plus, dès lors que l’utilisateur entre un opérande qui est un opérateur, la ligne de commande est automatiquement évaluée.

## Modularité de l’application

Une caractéristique importante dans la réalisation de ce projet (et dans la réalisation de tout projet orienté objet) 
a été de faire en sorte de permettre facilement des évolutions dans notre application.

### Les littérales et Opérateurs

Les littérales et les opérateurs sont fabriqués dans des *fabriques* dédiées. Il existe donc une classe concrète pour chaque 
type de littérale (Entier, Réel, ...) et pour chaque type concret d’opérateur (Plus, Moins, ...). Ainsi, il est très facile 
d’ajouter (ou même supprimer) un type de littérale ou d’opérateur.

L’ajout d’une littérale ou d’un opérateur entraîne l’ajout de code et non la modification de certaines parties de celui-ci 
déjà existant. Il sera nécessaire pour une littérale de renseigner certaines méthodes indispensables comme **toString()** 
permettant l’affichage de la littérale dans la pile ; et pour un opérateur de déclarer et définir une méthode décrivant 
son action. Il faut également savoir et renseigner de quelle classe abstraite la littérale ou l’opérateur hérite.

De plus, ajouter un nouveau type de littérale n’entrera pas en conflit avec la sauvegarde de contexte puisqu’on ne 
stocke que l’information *littérale* et non le type de celle-ci.

### Item

La classe **Item** vient encapsuler une instance d’un objet de la classe **Litterale**, et cela permet une certaine évolutivité 
dans notre application. En effet, il aurait tout à fait été possible d’empiler directement des objet **Litterale** dans la 
pile, mais le fait de passer par une classe **Item** permettrait par exemple d’empiler non seulement une littérale mais 
également des informations supplémentaires sur cette littérale, simplement en ajoutant des attributs dans la classe **Item**.

### CareTaker


La classe **CareTaker** joue le rôle de sauvegarde des états successifs de la pile, et l’on pourrait alors très 
facilement en adaptant le code existant, choisir l’état de la pile auquel on souhaite revenir, ou bien même ajouter 
des commentaires aux états que l’on sauvegarde afin de pouvoir les parcourir plus facilement ultérieurement.

## Éventuelles améliorations et remarques

Le projet de conception et de réalisation d’une calculette scientifique nous a demandé beaucoup de temps, c’est pourquoi 
nous n’avons pas pu réaliser l’ensemble des fonctionna- lités qui étaient demandées. Pour obtenir une application 
pleinement fonctionnelle, nous sommes conscient qu’il faudrait porter quelques améliorations à notre code.
— Dans la gestion des exceptions tout d’abord, il aurait peut-être été plus judicieux de séparer les classes **Exception** 
en plusieurs classes afin de détecter quel type d’erreur est soulevé. De plus, pour de simples erreurs de frappe, comme 
un oubli de crochet en fin de programme, il aurait été intéressant de proposer à l’utilisateur une correction.
— L’application graphique n’était pas le but premier dans ce projet, c’est pourquoi nous n’avons pas porté une attention 
poussée sur le design de l’application et son ergonomie. En vue d’un développement plus poussé de la calculette, on 
pourrait améliorer la qualité visuelle du rendu global.
— Le *parsing* de la ligne de commande pourrait certainement être amélioré et optimisé afin de convenir à des expressions 
de très grande taille.
— L’utilisation d’un outil de débuggage comme **Valgrind** pourrait être une bonne stratégie étant donné la grande quantité 
de code qui compose l’application. Celui- ci permet notamment la détection de fuites de mémoires et de portions de codes 
inutilisées. Cela pourrait permettre d’optimiser au maximum la calculette tout en minimisant le code.
— L’utilisation de la méta-programmation, et notamment des **templates** aurait pu être intéressante à certains endroits 
du programme, pour éviter la redondance dans le code et fluidifier la lecture du code source.
— La sauvegarde du contexte aurait pu être davantage poussée. En effet, nous avons choisi de partir sur un fichier XML 
étant donné le peu de données à traiter. Cependant dans une optique d’une application plus complète, il serait peut être 
plus judicieux de développer un système de sauvegarde de contexte sur une base de données.

De plus, dans notre cas, la sauvegarde dans un fichier **Xml** ne marche pas sous Mac OS, c’est pourquoi nous ne nous 
n’avons pas accordé beaucoup d’importance à cette partie, et la sauvegarde des paramètres de la pile n’a pas été faite.

## Conclusion

La réalisation de ce projet, bien que très demandeuse de temps, nous a beaucoup ap- porté dans le domaine de la programmation 
orientée objet. Cela nous a permis de gérer le développement complet d’une application, de sa conception formelle en 
langage **UML** jusqu’à sa réalisation à proprement parlé en **C++**. Nous avons pu nous rendre compte des réelles 
difficultés liées à un développement de cette envergure, comme la répartition des tâches au sein du binôme, ou 
l’utilisation de technologies peu connues comme **Qt**. La question de l’architecture de l’application nous a demandé 
beaucoup d’effort car il a fallu nous renseigner sur les différents design pattern qui existent afin d’optimiser et de 
concevoir au mieux notre application dès le début pour éviter de revenir dessus ultérieurement.

Au final, nous obtenons une application fonctionnelle et répondant le mieux possible aux attentes émises dans le sujet. 
Cependant, nous sommes conscients des améliorations et optimisations qui pourraient être apportées à notre code afin de 
rendre l’application plus robuste.