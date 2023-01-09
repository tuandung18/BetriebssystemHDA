# Aufgabe 4 im Praktikum: Betriebssysteme

> **Vorlesung Betriebssysteme  
    Wintersemester 2022/23  
    Prof. Dr. Ronald Moore  
    Fachbereich Informatik  
    Hochschule Darmstadt**


In dieser Aufgabe sollen mit C++11 Threads zwei Lösungen für das klassische Reader/Writer Problem verglichen werden.

## Hilfsmittel

Zuerst sollen Sie Kapitel IV vom Skript lesen.  Das ist nicht nur empfehlenswert, sondern _notwendig_ -- Absatz IV.C.ii wird hier verwendet (s.u.).

Weiter wird Ihnen Code zur Verfügung gestellt. Sie können dieses Repository klonen und danach weiter entwickeln.

Die Datei bzw. das Repository beinhaltet vier Programme -- oder genauer gesagt, zwei Programme, jeweils in zwei Versionen: einmal mit POSIX-Threads und einmal mit C++11-Threads. Die zwei Programme sind:

1. `wrong-reader-writer`: eine **nicht** korrekte Lösung für das Leser-Schreiber-Problem, die allerdings Werkzeuge für das Schreiben in bzw. Lesen von einer (simulierten) Datenbank bereitstellt. Dieses Programm wird von Ihnen weiterentwickelt (s.u.). 

1. `philosophen`:  eine korrekte Lösung für das Problem der speisenden Philosophen. Das Programm kann (nur) verwendet werden, um festzustellen, ob Ihre Entwicklungsumgebung für multithreaded Programmierung mit C++11 richtig aufgestellt ist. Dieses Programm sollten Sie **nicht** weiterentwickeln.
  
Die POSIX-Threads-Versionen sind nicht empfohlen.  C++-Threads sind empfohlen.

Das Programm `wrong-reader-writer` sollen Sie wie folgt weiter entwickeln: 
Sie sollen zwei _richtige_ Lösungen für das Leser-Schreiber-Problem entwickeln und vergleichen, wie unten beschrieben.

## Erste Lösung: Reader bevorzugt

Programmieren Sie zuerst die Lösung des Leser-Schreiber-Problems, die Leser bevorzugt.  Nehmen Sie diese Lösung vom Skript, Kapitel IV, Absatz C.ii.
Sie müssen "nur" den Pseudo-Code in echten Code übersetzen.

Sie sollen nur die Datei `reader-writer-threads.cpp` ändern -- wobei Sie sowohl die Funktion `reader` als auch die Funktion `writer` ändern sollen.

Sie sollen weiter nur sehr wenige (vielleicht ein Dutzend) Zeilen neues Code addieren! 
Wenn Sie viel mehr als das programmieren, haben Sie etwas falsch verstanden.

Jeder Thread liest von bzw. schreibt in einer gemeinsamen "Datenbank". Die Datenbank wird so simuliert, sodass:

1. die Operationen nicht ganz trivial sind und
1. nicht korrekte Operationen auffallen. Das Programm ist also selbst-testend. 

Experimentieren Sie mit einer verschiedenen Anzahl Threads, und verschiedenen Mischungen von lesenden und schreibenden Threads (zum Beispiel: 9 lesende Threads für jeden schreibenden Thread; gleich viele lesende und schreibende Threads; ein lesender Thread für je 9 schreibende Threads; usw).

(Erst) wenn Sie überzeugt sind, dass Ihr Programm richtig ist, bemessen Sie wie viele Schreib- und Leseoperationen in einem gegebenen Zeitraum geleistet werden können.
Hierfür sollen Sie das Programm mehrere Minuten laufen lassen, und zwar mit viele Threads (z.B. mit 10 Leser und 90 Schreiber, und dann mit 90 Leser und 10 Schreiber und dann mit 50 Leser und 50 Schreiber).

*Das heißt, machen Sie verschiedene Messungen, schreiben Sie die Messungen auf, und analysieren Sie Ihre Ergebnisse. Unter welchen Bedingungen wird z.B. die Benachteiligung der Schreiber deutlich?*

**Warnungen** (Fehler, die in der Vergangenheit beliebt waren):

  1.  Testläufe, die weniger als eine Minute dauern, haben keine Aussagekraft und werden nicht akzeptiert. Fünf Minuten sind noch besser (usw.).
  1.  Bei alle Testläufe soll am Ende stehen, dass die Datenbank in Ordnung ist.  
      Sonst ist das Programm noch nicht richtig und muss noch (weiter) korrigiert werden.
  2.  Die Schutzmechanismen, die Sie zum Programm addieren, müssen Sie so einbauen, dass jede Lese- bzw. Schreiboperation _einzeln_ geschützt wird.   Anders formuliert: Aufrufe zu `sleep` (bzw. ` std::this_thread::sleep_for`) sollen _nicht_ geschützt werden, die sollen außerhalb des "kritischen Bereichs" liegen.


## Zweite Lösung: Fairere Behandlung von Leser und Schreiber

Entwickeln und programmieren Sie eine zweite Lösung für das Leser-Schreiber-Problem, mit der Absicht, die Schreiber nicht so lange warten zu lassen.

Überlegen Sie zuerst so genau wie möglich, welches Verhalten Sie erreichen wollen: Wann soll welche Art Operation zugelassen werden? Wann soll auf was gewartet werden? Das heißt, dass Sie definieren bzw. präzisieren, was "fairer" heißt; Bitte fragen Sie den Dozenten nicht, was "fair" hier bedeutet, sondern seien Sie bereit, ihm zu erklären, was Sie unter "fair" verstehen.

Eine Einschränkung: Es müssen immer mehr als ein Reader gleichzeitig lesen können. Eine Lösung, wo entweder ein Leser liest oder ein Schreiber schreibt (und niemals mehrere Reader gleichzeitig lesen) ist zu einfach, gilt aus unfair (für die Leser) und wird **nicht akzeptiert.**
 
Experimentieren Sie auch hier mit einer verschiedenen Anzahl Threads, und verschiedenen Mischungen von lesenden und schreibenden Threads -- _genau_ wie bei Ihrer erste Lösung. 
Bemessen Sie wie oben die Anzahl der erfolgten Lese- und Schreiboperationen. 
Vergleichen Sie das Verhalten der zwei Lösungen, und stellen Sie fest, unter welchen Bedingungen die erste bzw. die zweite Lösung die bessere ist.

Das heißt, machen Sie wieder verschiedene Messungen, schreiben Sie die Messungen auf, und analysieren Sie Ihre Ergebnisse. 
Nehmen Sie die Messungen so auf, dass sie aussagekräftig sind! 

**Warnung** Gute (und nicht so gute) Lösungen sind im Internet zu finden. 
Es ist erlaubt, sie zu verwenden -- vorausgesetzt, dass Sie sie benennen. 
Schreiben Sie auf, woher Sie Ideen bzw. Code genommen haben, sowohl als Kommentar im Code und auch in ihrem Labor-Bericht.

## Labor-Bericht

Präsentieren Sie die Ergebnisse ihrer Analyse als ein Labor-Protokoll, d.h. eine pdf-Datei. 

Die Qualität der Analyse ist wichtiger als die Verbesserung der Leistung durch die zweite Lösung!

Laden Sie das Labor-Protokoll (pdf-Datei) sowohl *in Moodle* als auch nach code.fbi.h-da.de hoch.

**Hinweis:** Die Namen der Autor:Innen muss in der Datei, als Teil des Berichts (gleich am Anfang (unter der Titel)) zu finden sein.
Wenn Ihre Name nicht dabei ist, wird der Dozent annehmen, dass Sie nichts beigetragen haben.

Ronald Moore <mailto:ronald.moore@h-da.de>

