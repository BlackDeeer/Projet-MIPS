# Explication du code de lecture d'instruction

## Déroulement :

    On récupère une instruction MIPS : "ADD $1 $2 $3"
    Elle est au format string

     On va découper le string en plusieurs parties comme ceci :

        `*data* = ["ADD","$1","$2","$3"]`
    
    `*data*` est un tableau de pointeurs ou chaque pointeur correspond à la chaine de caractère découpée.

    - On va ensuite chercher l'opération data[0] <=> "ADD" dans une **table**

        La table d'instruction est un fichier texte contenant des informations sur la lecture des instructions :

            OPERATION opcode TYPE op1 op2 op3 op4

        Pour le "ADD" on pourra trouver :

            ADD 100000 R r2 r3 r1 0
        
        Comment on lit ça ?
            l'instruction est de type "R" alors l'opération traduite sera sous cette forme

                | SPECIAL | ? | ? | ? | ? | OPCODE |
                | 6  bits |   4 x 5 bits  | 6 bits |

            on a déja l'opcode en première position derrière le mot-clef de l'instruction (table[k+1])
            on sait aussi que pour toutes nos instructions ici on aura SPECIAL = "000000"
            alors :

                | 000000 | ? | ? | ? | ? | 100000 |

            enfin on a des information sur l'organisation des éléments au centre :

                | 000000 | r2 | r3 | r1 | 0 | 100000 |

            rX signifie que c'est la place du Xième registre de l'instruction, ici :

                r1 <=> "$1"     r2 <=> "$2"     r3 <=> "$3"

                (On prendra bien sur que les entières derrière le "$")
            

            0 signie qu'on aura un vecteur de 5 bits nuls : "00000"

            on a finalement :

            | 000000 | 2 | 3 | 1 | 0 | 100000 |

        Le programme effectue  cette lecture et convertit tout en bianire :

        0b0000000001000011000010000010000

        Pour enfin donner et hexa :

        0x00430820

