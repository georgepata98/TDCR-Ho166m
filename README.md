In main.cc se modifica numarul de evenimente care sa fie simulate.
In run.cc, in constructor, se modifica numarul de bini si range-ul binilor.
In gps.mac se modifica pozitia sursei (daca este cazul, in functie de inaltimea LS care contine materialul radioactiv) precum si energia.

In folderul results se afla programul hists-merger.C care pune toate histogramele pentru fiecare linie gama pe aceeasi histograma si le scaleaza in functie de intensitatile de emisie. Se modifica in program numele fisierelor root, nr. histogramelor, nr. de bini per histograma si grosimea in keV a unui bin (in ultimul for de la sfarsit).
Tot in folderul results se afla programul root-to-txt-hist.C care salveaza histogramele din fisierele root in fisiere text.
