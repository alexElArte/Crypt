# Crypt
Un moyen simple de (dé)crypter des données. D'après mes réflexions, ce code est difficilement violable.

Vous avez deux fichiers, l'un pour créer des clés de cryptage et l'autre le code pour crypter/décrypter des données.

Plus d'info:

  Mask: C'est une méthode pour cacher des données
    C'est une simple opération au niveau binaire.
    Voici comment cela fonctionne:
      *1^1 = 0     (Le ^ est l'oppération XOR)
      *0^1 = 1
      *1^0 = 1
      *0^0 = 0
    Si deux bits ont la même valeur le résultat sera 0, si les deux bits ont une valeur différente le résultat sera 1.
    
    ex:
      11110000
             |---->00110011
      11001100
    
      Dans le cas de mon programme je fait un mask de la valeur V avec la valeur V-1 donc la valeur précédente
    
      0000  --> 1110 (Cette valeur est calculée en dernier et prend donc le mask de la dernière valeur du tableau 1110^0000=1110) etape 4
      0010  --> 0010 (Je calcule cette valeur en premier, elle ne change pas car le masque est 0000)                              etape 1
      0100  --> 0110 (J'utilise la valeur précédement calculée: 0010^0100=0110)                                                   etape 2
      1000  --> 1110 (Je fais la même chose 0110^1000=1110)                                                                       etape 3
      
      
      Pour le décryptage c'est la même chose dans le sens inverse:
      
      1110  --> 0000 (Je calcule cette valeur en premier avec la dernière valeur du tableau donc 1110^1110=0000)                  etape 1
      0010  --> 0010 (Je continue avec la valeur précédement calculée 0010^0000=0010)                                             etape 4
      0110  --> 0100 (Même chose 0110^0010=0100)                                                                                  etape 3
      1110  --> 1000 (Je commence par cette valeur après la première avec celle au-dessus 1110^0110=1000)                         etape 2

  Déplacement: C'est une méthode pour changer les données de places dans un tableau pour les rendre illisibles.
    key = {6, 8, 7, 9, 5, 4, 3, 2, 1, 0};
    data = {56, 78, 16, 38, 98, 21, 18, 85, 91, 61};
  
    key est un tableau donc chaque donnée a un index
    ex: 
      -l'index de 9 est 0
      -l'index de 5 est 4
      -etc
    
    Dans notre cas le tableau data sera:
      data --> {61,91, 85, 18, 21, 98, 56, 16, 78, 38}
    
    Dans mon code c'est écrit:
      for (byte i = 0; i < keylen; i++) {
        data1[ key[i] ] = data[i];
      }
    Au lieu de mettre la donnée data au même index que data1 on le change, si on change les valeur de i:
      data1[ key[0] ] = data[0]   <=>   data1[6] = 56
      data1[ key[1] ] = data[1]   <=>   data1[8] = 78
      data1[ key[2] ] = data[2]   <=>   data1[7] = 16
      data1[ key[3] ] = data[3]   <=>   data1[9] = 38
      data1[ key[4] ] = data[4]   <=>   data1[5] = 98
      data1[ key[5] ] = data[5]   <=>   data1[4] = 21
      data1[ key[6] ] = data[6]   <=>   data1[3] = 18
      data1[ key[7] ] = data[7]   <=>   data1[2] = 85
      data1[ key[8] ] = data[8]   <=>   data1[1] = 91
      data1[ key[9] ] = data[9]   <=>   data1[0] = 61
    Donc ça nous donne:
      data1 --> {61, 91, 85, 18, 21, 98, 56, 16, 78, 38}
    
    
    Pour le décryptage c'est pareil mais dans le sens inverse.
    La fonction est:
      for (byte i = 0; i < 32; i++) {
        data[i] = data1[ key[i] ];
      }
    Si on fait la même chose qu'au-dessus:
      data[0] = data1[ key[0] ]   <=>   data[0] = data1[6]   <=>   data[0] = 56
      data[1] = data1[ key[1] ]   <=>   data[1] = data1[8]   <=>   data[1] = 78
      data[2] = data1[ key[2] ]   <=>   data[2] = data1[7]   <=>   data[2] = 16
      data[3] = data1[ key[3] ]   <=>   data[3] = data1[9]   <=>   data[3] = 38
      data[4] = data1[ key[4] ]   <=>   data[4] = data1[5]   <=>   data[4] = 98
      data[5] = data1[ key[5] ]   <=>   data[5] = data1[4]   <=>   data[5] = 21
      data[6] = data1[ key[6] ]   <=>   data[6] = data1[3]   <=>   data[6] = 18
      data[7] = data1[ key[7] ]   <=>   data[7] = data1[2]   <=>   data[7] = 85
      data[8] = data1[ key[8] ]   <=>   data[8] = data1[1]   <=>   data[8] = 91
      data[9] = data1[ key[9] ]   <=>   data[9] = data1[0]   <=>   data[9] = 61
    Donc ça nous donne:
      data --> {56, 78, 16, 38, 98, 21, 18, 85, 91, 61}
    
    Ce tableau correspond à celui du début.
