# Λειτουργικά Συστήματα 2017 - 2018
Στην αρχή του προγράμματος ελέγχεται ο αριθμός των ορισμάτων κατά την εκτέλεση του shell, ώστε να αποφανθούμε για το mode.

Διαβάζουμε μία σειρά εντολών. Αν είμαστε στο interactive mode από τον χρήστη, αλλιώς στο batch mode από αρχείο.

Χωρίζουμε τη σειρά στα semicolons (;) και για κάθε ένα token που προκύπτει το χωρίζουμε στα διπλά ampersands (&&).

Αφαιρούμε τα κενά από την αρχή και το τέλος της εντολής.

Ελέγχουμε αν ο χρήστης έγραψε την εντολή quit για να τερματίσουμε το κέλυφος ή να συνεχίσουμε με την εκτέλεση των εντολών.

Για μη κενή εντολή, κάνουμε fork και στο child process εκτελούμε την εντολή αφού πρώτα διαχωρίσουμε τα ορίσματά της.

Για επιτυχή εκτέλεση η evecvp "σκοτώνει" τη διεργασία, αλλιώς επιστρέφει την τιμή -1 και τερματίζουμε την child process.

Σε κάθε περίπτωση η parent process περιμένει το παιδί να ολοκληρωθεί.

Αν η εκτέλεση της τελευταίας εντολής απέτυχε, τότε σταματάμε για τις υπόλοιπες που ακολουθούν τα &&.
