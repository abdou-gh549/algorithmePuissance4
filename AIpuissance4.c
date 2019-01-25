#include "puissance4.h"
#include "AIpuissance4.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
int megaMax(partie *p, int profondeur);
int megaMaxNbrCoup(partie *p, int nombreCoup);
int megaMaxAI3(partie *p, int profondeur);
int megaMaxAlphBeta(partie *p, int profondeur, int alpha, int beta);
int megaMaxAlphBetaAvecTrie(partie *p, int profondeur, int alpha, int beta);

int AIPlayerX(partie *p, mouvement *m, int algorithme){
   liste_mouvements lm;
   int i;
   int bscore = -1000000;
   int bmove=-1;
   int nb_bscore=1;
   int nb_moves= remplit_liste_mouvements(p,&lm);
   for (i=0;i<nb_moves;i++) {
       partie *p2;
       int scoretmp;
        p2=joue_coup_suivant(p,&(lm.liste[i]));

       switch(algorithme){
        case 0:
                scoretmp = get_score(p2) * get_joueur(p);
            break;
        case 1:
                scoretmp = - megaMax(p2,4);
            break;
        case 2:
                scoretmp = - megaMaxNbrCoup(p2, 10000 / nb_moves);
            break;
        case 3:
                scoretmp = - megaMaxAI3(p2, 4);
            break;
        case 4:
                scoretmp = - megaMaxAlphBeta(p2,4,-100001,100001);
            break;

        case 5:
                scoretmp = - megaMaxAlphBetaAvecTrie(p2,4,-100001,10001);
        break;
       }
       if (scoretmp>bscore) { bscore=scoretmp; bmove=i; nb_bscore=1; }
       else if ((scoretmp == bscore) && (rand()%(++nb_bscore)==0)) {
            bscore=scoretmp; bmove=i;
       }
   }
   memcpy(m,&(lm.liste[bmove]),sizeof(mouvement));
   return bscore;
}

/* joueur par défaut (-1) : cette fonction fait juste un appel à AIplayer[0-5] */
int AIplayer(partie *p, mouvement *m) {
    return AIplayer0(p,m);
}

/* joueur 0 : sans algorithme minimax, illustre l'usage des fonctions manipulant les parties */
int AIplayer0(partie *p, mouvement *m) {
    return AIPlayerX(p,m,0);
}


////////////////////////////////////////////////
//////////////// AIplayer1 /////////////////////
////////////////////////////////////////////////

int megaMax(partie *p, int profondeur){
    if(p->termine == 1 || profondeur <= 0){
        return get_score(p) * get_joueur(p);
    }
   liste_mouvements lm;
   int i;
   int bscore = -1000000;
   int bmove=-1;
   int nb_bscore = 1;
   int nb_moves = remplit_liste_mouvements(p,&lm);

   for (i=0;i<nb_moves;i++) {
       int scoretmp;

       scoretmp = - megaMax( joue_coup_suivant(p,&(lm.liste[i])) , profondeur - 1);

       if (scoretmp>bscore) { bscore=scoretmp; bmove=i;nb_bscore = 1;}

       else if ((scoretmp==bscore) && (rand()%(++nb_bscore)==0)) {
            bscore=scoretmp; bmove=i;
       }

   }
   return bscore;
}

int AIplayer1(partie *p, mouvement *m) {
    return AIPlayerX(p,m,1);
}

////////////////////////////////////////////////
//////////////// AIplayer2 /////////////////////
////////////////////////////////////////////////

int megaMaxNbrCoup(partie *p, int nombreCoup){
    if(p->termine == 1 || nombreCoup < 1 ){
        return get_score(p) * get_joueur(p);
    }
   liste_mouvements lm;
   int i;
   int bscore = -1000000;
   int bmove=-1;
   int nb_bscore = 1;
   int nb_moves = remplit_liste_mouvements(p,&lm);

   for (i=0;i<nb_moves;i++) {
       int scoretmp;

       scoretmp = - megaMaxNbrCoup(joue_coup_suivant(p,&(lm.liste[i])), nombreCoup / nb_moves);

       if (scoretmp>bscore) { bscore=scoretmp; bmove=i;nb_bscore = 1;}
       else if ((scoretmp==bscore) && (rand()%(++nb_bscore)==0)) {
            bscore=scoretmp; bmove=i;
       }
   }
   return bscore;
}

int AIplayer2(partie *p, mouvement *m) {
    return AIPlayerX(p,m,2);
}

////////////////////////////////////////////////
//////////////// AIplayer3 /////////////////////
////////////////////////////////////////////////

int megaMaxAI3(partie *p, int profondeur){
    if(p->termine == 1 || profondeur <= 0){
        return get_score(p) * get_joueur(p);
    }
   liste_mouvements lm;
   int i;
   int bscore = -1000000;
   int bmove=-1;
   int nb_bscore = 1;
   int nb_moves = remplit_liste_mouvements(p,&lm);

   for (i=0;i<nb_moves;i++) {
       int scoretmp;
       scoretmp = - megaMaxAI3( joue_coup_suivant(p,&(lm.liste[i])) , profondeur - 1);
       if (scoretmp>bscore) {
           bscore=scoretmp;
           bmove=i;
           nb_bscore = 1;
       }
       else if ((scoretmp==bscore) && (rand()%(++nb_bscore)==0)) {
            bscore=scoretmp; bmove=i;
       }
   }
   if(bscore <= -1000)
        return bscore + 1;
    else if(bscore >= 1000)
        return bscore - 1;
    else
        return bscore;
}

int AIplayer3(partie *p, mouvement *m) {
    return AIPlayerX(p,m,3);
}

////////////////////////////////////////////////
//////////////// AIplayer4 /////////////////////
////////////////////////////////////////////////


int megaMaxAlphBeta(partie *p, int profondeur, int alpha, int beta){

    if(p->termine == 1 || profondeur <= 0){
        return get_score(p) * get_joueur(p);
    }
   liste_mouvements lm;
   int i;
   int bscore = -1000000;
   int bmove=-1;
   int nb_bscore = 1;
   int nb_moves = remplit_liste_mouvements(p,&lm);
   for (i=0;i<nb_moves;i++) {

       int scoretmp;
       scoretmp = - megaMaxAlphBeta( joue_coup_suivant(p,&(lm.liste[i])) , profondeur - 1, -beta, -alpha);

       if (scoretmp>bscore) {
           bscore=scoretmp;
           bmove=i;
           nb_bscore = 1;
       }
       else if ((scoretmp==bscore) && (rand()%(++nb_bscore)==0)) {
            bscore=scoretmp; bmove=i;
       }
       /// alpha condition
       if(bscore > alpha)
                alpha = bscore;

           if(alpha >= beta){
                return bscore;
           }
   }

   if(bscore <= -1000)
        return bscore + 1;
    else if(bscore >= 1000)
        return bscore - 1;
    else
        return bscore;

}

int AIplayer4(partie *p, mouvement *m) {
    return AIPlayerX(p,m,4);
}

////////////////////////////////////////////////
//////////////// AIplayer5 /////////////////////
////////////////////////////////////////////////

int megaMaxAlphBetaAvecTrie(partie *p, int profondeur, int alpha, int beta){

    if(p->termine == 1 || profondeur <= 0){
        return get_score(p) * get_joueur(p);
    }
   liste_mouvements lm;
   int i;
   int bscore = -1000000;
   int bmove=-1;
   int nb_bscore = 1;
   int nb_moves = remplit_liste_mouvements(p,&lm);
   tri_liste_mouvements(p,&lm);
   for (i=0;i<nb_moves;i++) {
       int scoretmp;
       scoretmp = - megaMaxAlphBeta( joue_coup_suivant(p,&(lm.liste[i])) , profondeur - 1, -beta, -alpha);
       if (scoretmp>bscore) {
           bscore=scoretmp;
           bmove=i;
           nb_bscore = 1;
       }
       else if ((scoretmp==bscore) && (rand()%(++nb_bscore)==0)) {
            bscore=scoretmp; bmove=i;
       }
       /// alpha condition
       if(bscore > alpha)
                alpha = bscore;

       if(alpha >= beta){
            return bscore;
       }
   }

    if(bscore <= -1000)
        return bscore + 1;
    else if(bscore >= 1000)
        return bscore - 1;
    else
        return bscore;

}
int AIplayer5(partie *p, mouvement *m) {

    return AIPlayerX(p,m,5);
}
