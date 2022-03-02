In this exercise it seems like a music player job (working with a playlist).
We will scan the database of songs from a file.
Our software will know how to do the following:
1. Play a song) will print the current song (screen) on the screen
2. Transition between songs (forward / backward)
3. Search for a song (by artist / song name / album name (- will display all search results
4. Deleting a song - should also be done in the song list file.
5. Adding a song - should also be done in the song list file.
6. Sort playlist by artist name / album name / song name
7. Mixing the playlist - 10 points bonus
Write a program that receives a file containing a list of songs from an argument.
Scanned file structure:
ID Artist Name Album Name Track Name Track No
132 Avatar Avatar Country "A Statue of the King" 7
543 Black Rebel Motorcycle Club Wrong Creatures "Echo" 5
876 Black Veil Brides Vale "Wake Up" 3
135 Children's Blue Madonna "Blue Madonna" 11
86 Camila Cabello Camila "Havana" 16
687 Corrosion of Conformity No Cross No Crown "E.L.M." 12
546 Francesca Michielin 2640 "Tropicale" 5
2 Joe Satriani What Happens Next "Headrush" 7
All messages printed on the screen should be copied to a log file.
To print a new record in a file, use the fprint function as follows:
fprintf (fp, "% - 5d% -30s% -30s% -30s% -5d \ n", par1, par2, par3, par4, par5); q
Remarks:
* It is possible and desirable to edit the implementation of the linked list that you received in such a way that the running time will be optimal
Most, or alternatively offer another realization.
* Beyond individual variables and a single two-way linked list, no additional structures can be used.
* In cases of dynamic allocation, care must be taken to release memory.
* Serving in pairs or singles only! Copy cases will be handled severely