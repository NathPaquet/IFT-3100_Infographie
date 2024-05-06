## Compilation

Pour pouvoir faire la compilation du projet sur un ordinateur, il est n�cessaire d�avoir la version 0.12.0
d�OpenFrameworks pour Visual Studio. En effet, il s�agit de la version d�OpenFrameworks qui a �t� utilis�
pour le d�veloppement de l�application sur Visual Studio. Il est possible de faire l�installation de ce framework
en consultant cette page : OpenFrameworks.

Par la suite, il est n�cessaire de faire l�installation d�un addon externe qui ne vient pas avec OpenFrameworks
par d�faut. Il s�agit d�un addon pour utiliser ImGui directement dans une application OpenFrameworks. Afin
de faire l�installation, on doit se diriger dans le r�pertoire �addons� qui se trouve � la racine du r�pertoire
d�OpenFrameworks. Une fois dans ce r�pertoire il faut faire la commande suivante :

git clone https://github.com/Daandelange/ofxImGui.git

La prochaine �tape est de venir faire le clonage du r�pertoire Git de l�application. Pour ce faire, il suffit d�aller
dans le r�pertoire �app� qui se trouve � la racine du r�pertoire d�OpenFrameWorks et de faire la commande
suivante :

git clone https://github.com/NathPaquet/Infographie_IFT-3100.git

Une fois le code source clon� directement dans le r�pertoire d�OpenFrameWorks, il suffit de lancer le projet-
Generator.exe (qui se trouve dans le r�pertoire projetGenerator). Puis, de cliquer sur le bouton �import�, et
s�lectionner le r�pertoire �Infographie_IFT-3100� que nous avons clon� � l��tape pr�c�dente. Il faut ensuite
ajouter les addons suivant en les s�lectionnant directement dans le dropbox : ofxAssimpModelLoader, ofxGui,
ofxImGui et ofxSVG. On clique sur le bouton �Generate� par la suite pour g�n�rer le projet avec toutes les
d�pendances.

Une fois toutes ces �tapes compl�t�es, il suffit de venir lancer l�application � partir de Visual Studio en
ouvrant la solution. Il est important d�avoir le Workloads : Desktop development with C++ sur Visual
Studio Community 2022 pour faire le d�veloppement.