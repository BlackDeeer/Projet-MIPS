# Explication du code de lecture d'instruction

## Fonctionnement :

On récupère une instruction MIPS : `"ADD $1 $2 $3"`

- On va découper le string en plusieurs parties comme ceci :

        data = ["ADD","$1","$2","$3"]

    `data` est un tableau de pointeurs ou chaque pointeur correspond à la chaine de caractère découpée.
    

- On va ensuite chercher l'opération `data[0] <=> "ADD"` dans une `table`

    La table d'instruction est un fichier texte contenant des informations sur la lecture des instructions :

        OPERATION opcode TYPE op1 op2 op3 op4

    Pour le "ADD" on pourra trouver :

        ADD 100000 R r2 r3 r1 0

    Comment lit-on cela ?
    - l'instruction est de type "R" alors l'opération traduite sera sous cette forme

            | SPECIAL | ? | ? | ? | ? | OPCODE |
            | 6  bits |   4 x 5 bits  | 6 bits |

    - on a déja l'opcode en première position derrière le mot-clef de l'instruction (table[k+1])
        on sait aussi que pour toutes nos instructions ici on aura SPECIAL = "000000"
        alors :

            | 000000 | ? | ? | ? | ? | 100000 |

    - enfin on a des information sur l'organisation des éléments au centre :

            | 000000 | r2 | r3 | r1 | 0 | 100000 |

        - `rX` signifie que c'est la place du Xième registre de l'instruction, ici :

                r1 <=> "$1"     r2 <=> "$2"     r3 <=> "$3"
            (On prendra bien sur que les entières derrière le "$")


        - `0` signie qu'on aura un vecteur de 5 bits nuls : `"00000"`

        - `1` correspond à 1 codé sur 5 bits : `"00001"`

        - `b` signifie qu'une partie de l'instruction est sous la forme `offset(base)` on va isoler la base de l'offset

        - `o` on utilise la précédente découpe pour placer l'offset

    - on a finalement :

            | 000000 | 2 | 3 | 1 | 0 | 100000 |

- Le programme effectue  cette lecture et convertit tout en binaire :

    `0b0000000001000011000010000010000`

- Pour enfin donner en hexadécimal :

    `0x00430820`

On a préféré convertir d'abord tout en binaire plutot que de faire des décalages en décimal pour bien comprendre ce qu'il se passe.

# Explication du main

Après avoir coder en hexadécimale notre ligne d'assembleur, il nous faut excécuter l'opération et modifier les registres et les mémoires en conséquences. 

Première, on initialise les registres et la mémoire à zéro. 

Puis on traduit le code hexadécimal de l'opération en binaire. Il faut récupérer l'opcode de l'opération pour l'envoyer dans la bonne fonction du fichier opération. 

Si les 6 premiers bits de l'opcode sont vide, alors l'opcode se situe à la fin de la traduction binaire. Puis en fonction de l'opcode, on envoie la traduction binaire dans les fonctions associées aux fonctions. 

Dans chaque fonction, on découpe le binaire en fonction des données à récupérer.
Par exemple, on prend la valeur du registre RS qui est compris entre les bits 6 à 11. On traduit ce petit tableau binaire en un entier. Puis on lit ce qui se trouve en registre avec la fonction lecture_reg. 

On écrit enfin l'état des registres et mémoire dans un fichier text "state". 



