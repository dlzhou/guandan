
#include "genmoves.h"
using namespace std;

// value map, A/Grade => 13, 2 => 1, ..., K => 12
// Grade varies from A to K ( 1 ... 13)
const int vMap[] = {13, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
int getValue(int nCard, int grade)
{
    if(nCard == 52)
        return 14;
    if(nCard == 53)
        return 15;
    int tMap[13] = {0};
    for(int n=0; n<13; n++)
        tMap[n] = vMap[n];
    if(grade > 1) {
        tMap[grade-1] = 13;
        for(int i=grade; i<=13; i++)
           tMap[i%13] -= 1;
    }
    return tMap[nCard % 13];
}

void removeFromDeal(vector<int> &deal, int value)
{
    vector<int>::iterator it;
    for(it = deal.begin(); it != deal.end(); it++){
        if(*it == value)
        {
            deal.erase(it);
            break;
        }
    }
}

bool InShapes(vector<Shape> vSp, Shape sp)
{
   // sp.sort();
    for(int i=0; i<vSp.size(); i++){
        if(sp.isEqual(vSp[i]))
            return true;
    }
    return false;
}

bool InMoves(vector<Move> vMv, vector<int> vc)
{
    for(int i=0; i<vMv.size(); i++) {
        if(vMv[i].IsEqual(vc))
            return true;
    }
    return false;
}

vector<Move> findJokerBomber(int grade, 
        int dealMap[54], int dealValueMap[13], int dealValueList[13][10])
{
    vector<Move> vMv;
    if(dealMap[VICE_JOKER] == 2 
        && dealMap[JOKER] == 2) {
        vector<int> vc;
        vc.push_back(dealMap[VICE_JOKER]);
        vc.push_back(dealMap[VICE_JOKER]);
        vc.push_back(dealMap[JOKER]);
        vc.push_back(dealMap[JOKER]);
    }
    return vMv;
}


vector<Move> findPureSequencer(int grade,
        int dealMap[54], int dealMapEx[54], int dealMapList[54][2])
        {
            vector<Move> vMv;
            for(int i=1; i<10; i++) {
                for(int j=0; j<4; j++) {
                int nGrades = dealMap[grade - 1 + 13];
                if(dealMapEx[i + j * 13] > 0
                && dealMapEx[i+1 + j * 13] > 0
                && dealMapEx[i+2 + j * 13] > 0
                && dealMapEx[i+3 + j * 13] > 0
                && dealMapEx[(i+4)%13 + j * 13] > 0)  {
                vector<int> vc;
                for(int jj=0; jj<dealMapEx[i+j*13]; jj++) {
                    if(dealMapList[i+j*13][jj] == grade - 1 + 13 
                         && nGrades > 0) {
                    nGrades --;
                }
                vc.push_back(dealMapList[i+j*13][jj]);
                for(int jk=0; jk<dealMapEx[i+1+j*13]; jk++) {
                    if(dealMapList[i+1+j*13][jk] == grade - 1 + 13
                    && nGrades > 0) {
                        nGrades --;
                    } else if(dealMapList[i+1+j*13][jk] == grade - 1 + 13)
                           continue; 
                    vc.push_back(dealMapList[i+1+j*13][jk]);
                    for(int k=0; k<dealMapEx[i+2+j*13]; k++){
                        if(dealMapList[i+2+j*13][k] == grade - 1 + 13 
                        && nGrades > 0) {
                            nGrades --;
                        }  else if(dealMapList[i+2+j*13][k] == grade - 1 + 13)
                           continue;  
                        vc.push_back(dealMapList[i+2+j*13][k]);  
                        for(int l=0; l<dealMapEx[i+3+j*13]; l++){
                            if(dealMapList[i+3+j*13][l] == grade - 1 + 13 
                            && nGrades > 0) {
                                nGrades --;
                            } else if(dealMapList[i+3+j*13][l] == grade - 1 + 13) 
                                continue;                
                            vc.push_back(dealMapList[i+3+j*13][l]);
                            for(int m=0; m<dealMapEx[(i+4)%13+j*13]; m++){
                                if(dealMapList[(i+4)%13+j*13][m] == grade - 1 + 13
                                && nGrades > 0) {
                                    nGrades --;
                                }  else if(dealMapList[(i+4)%13+j*13][m] == grade - 1 + 13)
                                    continue;
                            vc.push_back(dealMapList[(i+4)%13+j*13][m]);
                                vector<int> tp(vc);
                                std::sort(tp.begin(), tp.end());
                                if(!InMoves(vMv, tp)){
                                    Move mv(PURE_SEQUENCER, getValue(i,grade), tp);
                                    vMv.push_back(mv);
                                }
                            vc.pop_back();
                        }
                        vc.pop_back();                     
                    }
                    vc.pop_back();
                }
                vc.pop_back();
            }
            vc.pop_back();
        }
    }
            }
   }
   return vMv;
}

vector<Move> findSequencer(int grade,
    int dealMap[54], int dealValueMap[13], int dealValueList[13][10])
{
    vector<Move> vMv;
    for(int i=1; i<10; i++) {
        int nGrades = dealMap[grade - 1 + 13];
        if(dealValueMap[i]>=1
         && dealValueMap[i+1]>=1
         && dealValueMap[i+2]>=1
         && dealValueMap[i+3]>=1
         && dealValueMap[(i+4)%13]>=1) {
            vector<int> vc;
            for(int jj=0; jj<dealValueMap[i]; jj++) {
                if(dealValueList[i][jj] == grade - 1 + 13 
                 && nGrades > 0) {
                    nGrades --;
                }  else if(dealValueList[i][jj] == grade - 1 + 13)
                           continue; 
                vc.push_back(dealValueList[i][jj]);
                for(int j=0; j<dealValueMap[i+1]; j++) {
                    if(dealValueList[i+1][j] == grade - 1 + 13 
                    && nGrades > 0) {
                        nGrades --;
                    } else if(dealValueList[i+1][j] == grade - 1 + 13)
                           continue; 
                    vc.push_back(dealValueList[i+1][j]);
                    for(int k=0; k<dealValueMap[i+2]; k++){
                        if(dealValueList[i+2][k] == grade - 1 + 13 
                        && nGrades > 0) {
                            nGrades --;
                        }  else if(dealValueList[i+2][k] == grade - 1 + 13)
                           continue;  
                        vc.push_back(dealValueList[i+2][k]);  
                        for(int l=0; l<dealValueMap[i+3]; l++){
                            if(dealValueList[i+3][l] == grade - 1 + 13 
                            && nGrades > 0) {
                                nGrades --;
                            } else if(dealValueList[i+3][l] == grade - 1 + 13) 
                                continue;                
                            vc.push_back(dealValueList[i+3][l]);
                            for(int m=0; m<dealValueMap[(i+4)%13]; m++){
                                if(dealValueList[(i+4)%13][m] == grade - 1 + 13
                                && nGrades > 0) {
                                    nGrades --;
                                    vc.push_back(dealValueList[(i+4)%13][m]);
                                    Move mv(SEQUENCER, getValue(i,grade), vc);
                                    vMv.push_back(mv);   
                                    vc.pop_back();                                
                                }  else if(dealValueList[(i+4)%13][m] == grade - 1 + 13)
                                    continue;                          
                        }
                        vc.pop_back();                     
                    }
                    vc.pop_back();
                }
                vc.pop_back();
            }
                vc.pop_back();
        }
        }
    }
    return vMv;
}

vector<Move> findSingle(int grade,
     int dealMap[54], int dealValueMap[13], int dealValueList[13][10])
{
        vector<Move> vMv;
        for(int i=0; i<13; i++) {
            if(dealValueMap[i]>=1) {
                vector<int> vc;
                for(int j=0; j<=dealValueMap[i]-1; j++) {
                    if(dealValueList[i][j] == grade - 1 + 13
                        && i!=grade)
                        continue;
                    vc.push_back(dealValueList[i][j]);
                    if(!InMoves(vMv, vc)){
                          Move mv(SINGLE, getValue(i,grade), vc);
                          vMv.push_back(mv);
                    }
                    vc.pop_back();
                }
            }
        }
    // Find Jokers
    for(int i=52; i<54; i++)
        if(dealMap[i] == 1) {
            vector<int> vc;
            vc.push_back(i);
            Move mv(SINGLE, getValue(i,grade), vc);
            vMv.push_back(mv);
        }
    return vMv;
}

vector<Move> findDouble(int grade,
     int dealMap[54], int dealValueMap[13], int dealValueList[13][10])
{
        vector<Move> vMv;
        for(int i=0; i<13; i++) {
            if(dealValueMap[i]>=2) {
                vector<int> vc;
                for(int j=0; j<=dealValueMap[i]-2; j++) {
                    vc.push_back(dealValueList[i][j]);
                    for(int k=j+1; k<=dealValueMap[i]-1; k++) {
                        vc.push_back(dealValueList[i][k]);
                        vector<int> tp(vc);
                        std::sort(tp.begin(), tp.end());
                        if(!InMoves(vMv, tp)){
                                 Move mv(DOUBLE, getValue(i,grade), tp);
                                 vMv.push_back(mv);
                            }
                            vc.pop_back();
                        }
                        vc.pop_back();
                    }
                }
            }
        // Find double Jokers
        for(int i=52; i<54; i++)
            if(dealMap[i] == 2) {
                vector<int> vc;
                vc.push_back(i);
                vc.push_back(i);
                Move mv(DOUBLE, getValue(i,grade), vc);
                vMv.push_back(mv);           
            }
        return vMv;
}

vector<Move> findTriple(int grade,
     int dealValueMap[13], int dealValueList[13][10])
{
        vector<Move> vMv;
        for(int i=0; i<13; i++) {
            if(dealValueMap[i]>=3) {
                vector<int> vc;
                for(int j=0; j<=dealValueMap[i]-3; j++) {
                    vc.push_back(dealValueList[i][j]);
                    for(int k=j+1; k<=dealValueMap[i]-2; k++) {
                        vc.push_back(dealValueList[i][k]);
                        for(int l=k+1; l<=dealValueMap[i]-1; l++) {
                                vc.push_back(dealValueList[i][l]);
                                vector<int> tp(vc);
                                std::sort(tp.begin(), tp.end());
                                if(!InMoves(vMv, tp)){
                                     Move mv(TRIPLE, getValue(i,grade), tp);
                                     vMv.push_back(mv);
                                }
                                vc.pop_back();
                            }
                         vc.pop_back();
                        }
                     vc.pop_back();
                    }
                }
            }
        return vMv;
}


vector<Move> findFourBombs(int grade,
     int dealValueMap[13], int dealValueList[13][10])
{
        vector<Move> vMv;
        for(int i=0; i<13; i++) {
            if(dealValueMap[i]>=4) {
                vector<int> vc;
                for(int j=0; j<=dealValueMap[i]-4; j++) {
                    vc.push_back(dealValueList[i][j]);
                    for(int k=j+1; k<=dealValueMap[i]-3; k++) {
                        vc.push_back(dealValueList[i][k]);
                        for(int l=k+1; l<=dealValueMap[i]-2; l++) {
                            vc.push_back(dealValueList[i][l]);
                            for(int m=l+1; m<=dealValueMap[i]-1; m++) {
                                vc.push_back(dealValueList[i][m]);
                                vector<int> tp(vc);
                                std::sort(tp.begin(), tp.end());
                                if(!InMoves(vMv, tp)){
                                     Move mv(FOUR_BOMB, getValue(i,grade), tp);
                                     vMv.push_back(mv);
                                }
                                vc.pop_back();
                                }
                                vc.pop_back();
                            }
                            vc.pop_back();
                        }
                        vc.pop_back();
                    }
                }
            }
        return vMv;
}


vector<Move> findFiveBombs(int grade,
     int dealValueMap[13], int dealValueList[13][10])
{
        vector<Move> vMv;
        for(int i=0; i<13; i++) {
            if(dealValueMap[i]>=5) {
                vector<int> vc;
                for(int j=0; j<=dealValueMap[i]-5; j++) {
                    vc.push_back(dealValueList[i][j]);
                    for(int k=j+1; k<=dealValueMap[i]-4; k++) {
                        vc.push_back(dealValueList[i][k]);
                        for(int l=k+1; l<=dealValueMap[i]-3; l++) {
                            vc.push_back(dealValueList[i][l]);
                            for(int m=l+1; m<=dealValueMap[i]-2; m++) {
                                vc.push_back(dealValueList[i][m]);
                                for(int n=m+1; n<=dealValueMap[i]-1;n++){
                                    vc.push_back(dealValueList[i][n]);
                                    vector<int> tp(vc);
                                    std::sort(tp.begin(), tp.end());
                                    if(!InMoves(vMv, tp)){
                                         Move mv(FIVE_BOMB, getValue(i,grade), tp);
                                         vMv.push_back(mv);
                                    }
                                    vc.pop_back();
                                    }
                                    vc.pop_back();
                                }
                                vc.pop_back();
                            }
                            vc.pop_back();
                        }
                        vc.pop_back();
                    }
                }
            }
        return vMv;
}

vector<Move> findSixBombs(int grade,
     int dealValueMap[13], int dealValueList[13][10])
{
        vector<Move> vMv;
        for(int i=0; i<13; i++) {
            if(dealValueMap[i]>=6) {
                vector<int> vc;
                for(int j=0; j<=dealValueMap[i]-6; j++) {
                    vc.push_back(dealValueList[i][j]);
                    for(int k=j+1; k<=dealValueMap[i]-5; k++) {
                        vc.push_back(dealValueList[i][k]);
                        for(int l=k+1; l<=dealValueMap[i]-4; l++) {
                            vc.push_back(dealValueList[i][l]);
                            for(int m=l+1; m<=dealValueMap[i]-3; m++) {
                                vc.push_back(dealValueList[i][m]);
                                for(int n=m+1; n<=dealValueMap[i]-2;n++){
                                    vc.push_back(dealValueList[i][n]);
                                    for(int o=n+1; o<=dealValueMap[i]-1; o++){
                                        vc.push_back(dealValueList[i][o]);
                                        vector<int> tp(vc);
                                        std::sort(tp.begin(), tp.end());
                                        if(!InMoves(vMv, tp)){
                                             Move mv(SIX_BOMB, getValue(i,grade), tp);
                                             vMv.push_back(mv);
                                        }
                                        vc.pop_back();
                                    }
                                    vc.pop_back();
                                }
                                vc.pop_back();
                            }
                            vc.pop_back();
                        }
                        vc.pop_back();
                    }
                    vc.pop_back();
                }
            }
        }
        return vMv;
}

vector<Move> findSevenBombs(int grade,
     int dealValueMap[13], int dealValueList[13][10])
{
        vector<Move> vMv;
        for(int i=0; i<13; i++) {
            if(dealValueMap[i]>=7) {
                vector<int> vc;
                for(int j=0; j<=dealValueMap[i]-7; j++) {
                    vc.push_back(dealValueList[i][j]);
                    for(int k=j+1; k<=dealValueMap[i]-6; k++) {
                        vc.push_back(dealValueList[i][k]);
                        for(int l=k+1; l<=dealValueMap[i]-5; l++) {
                            vc.push_back(dealValueList[i][l]);
                            for(int m=l+1; m<=dealValueMap[i]-4; m++) {
                                vc.push_back(dealValueList[i][m]);
                                for(int n=m+1; n<=dealValueMap[i]-3;n++){
                                    vc.push_back(dealValueList[i][n]);
                                    for(int o=n+1; o<=dealValueMap[i]-2; o++){
                                        vc.push_back(dealValueList[i][o]);
                                        for(int p=o+1; p<=dealValueMap[i]-1; p++){
                                            vc.push_back(dealValueList[i][p]);
                                            vector<int> tp(vc);
                                            std::sort(tp.begin(), tp.end());
                                            if(!InMoves(vMv, tp)){
                                                 Move mv(SEVEN_BOMB, getValue(i,grade), tp);
                                                 vMv.push_back(mv);
                                            }
                                            vc.pop_back();
                                        }
                                        vc.pop_back();
                                    }
                                    vc.pop_back();
                                }
                                vc.pop_back();
                            }
                            vc.pop_back();
                        }
                        vc.pop_back();
                    }
                    vc.pop_back();
                }
            }
        }
        return vMv;
}

vector<Move> findEightBombs(int grade,
     int dealValueMap[13], int dealValueList[13][10])
{
        vector<Move> vMv;
        for(int i=0; i<13; i++) {
            if(dealValueMap[i]>=8) {
                vector<int> vc;
                for(int j=0; j<=dealValueMap[i]-8; j++) {
                    vc.push_back(dealValueList[i][j]);
                    for(int k=j+1; k<=dealValueMap[i]-7; k++) {
                        vc.push_back(dealValueList[i][k]);
                        for(int l=k+1; l<=dealValueMap[i]-6; l++) {
                            vc.push_back(dealValueList[i][l]);
                            for(int m=l+1; m<=dealValueMap[i]-5; m++) {
                                vc.push_back(dealValueList[i][m]);
                                for(int n=m+1; n<=dealValueMap[i]-4;n++){
                                    vc.push_back(dealValueList[i][n]);
                                    for(int o=n+1; o<=dealValueMap[i]-3; o++){
                                        vc.push_back(dealValueList[i][o]);
                                        for(int p=o+1; p<=dealValueMap[i]-2; p++){
                                            vc.push_back(dealValueList[i][p]);
                                            for(int q=p+1; q<=dealValueMap[i]-1; q++){
                                                vc.push_back(dealValueList[i][q]);
                                                vector<int> tp(vc);
                                                std::sort(tp.begin(), tp.end());
                                                if(!InMoves(vMv, tp)){
                                                     Move mv(EIGHT_BOMB, getValue(i,grade), tp);
                                                     vMv.push_back(mv);
                                                }
                                                vc.pop_back();
                                            }
                                            vc.pop_back();
                                        }
                                        vc.pop_back();
                                    }
                                    vc.pop_back();
                                }
                                vc.pop_back();
                            }
                            vc.pop_back();
                        }
                        vc.pop_back();
                    }
                    vc.pop_back();
                }
            }
        }
        return vMv;
}

vector<Move> findTripleDoubles(vector<int> &deal, int grade,
                               int dealMap[54], int dealValueMap[13], int dealValueList[13][10])
{
    vector<Move> vMv;
    for(int i=1; i<13; i++) {
        if(dealValueMap[i] >= 3
           && dealValueMap[(i+1)%13] >= 3
           ) {
            int nGrades = dealMap[grade - 1 + 13];
            vector<int> vc;
            for(int jj=0; jj<dealValueMap[i]-2; jj++) {
                if(dealValueList[i][jj] == grade - 1 + 13
                   && nGrades > 0) {
                    nGrades --;
                }
                vc.push_back(dealValueList[i][jj]);
                for(int kk=jj+1; kk<dealValueMap[i]-1; kk++) {
                    if(dealValueList[i][kk] == grade - 1 + 13
                       && nGrades > 0) {
                        nGrades --;
                    } else if(dealValueList[i][kk] == grade - 1 + 13)
                        continue;
                    vc.push_back(dealValueList[i][kk]);
                    for(int kkk=kk+1; kkk<dealValueMap[i]; kkk++) {
                        if(dealValueList[i][kkk] == grade - 1 + 13
                           && nGrades > 0) {
                            nGrades --;
                        } else if(dealValueList[i][kkk] == grade - 1 + 13)
                            continue;
                        vc.push_back(dealValueList[i][kkk]);
                        for(int j=0; j<dealValueMap[(i+1)%13]-2; j++) {
                            if(dealValueList[(i+1)%13][j] == grade - 1 + 13
                               && nGrades > 0) {
                                nGrades --;
                            } else if(dealValueList[(i+1)%13][j] == grade - 1 + 13)
                                continue;
                            vc.push_back(dealValueList[(i+1)%13][j]);
                            for(int jk=j+1; jk<dealValueMap[(i+1)%13]-1; jk++) {
                                if(dealValueList[(i+1)%13][jk] == grade - 1 + 13
                                   && nGrades > 0) {
                                    nGrades --;
                                } else if(dealValueList[(i+1)%13][jk] == grade - 1 + 13)
                                    continue;
                                vc.push_back(dealValueList[(i+1)%13][jk]);
                                for(int jkk=jk+1; jkk<dealValueMap[(i+1)%13]; jkk++) {
                                    if(dealValueList[(i+1)%13][jkk] == grade - 1 + 13
                                       && nGrades > 0) {
                                        nGrades --;
                                    } else if(dealValueList[(i+1)%13][jkk] == grade - 1 + 13)
                                        continue;
                                    vc.push_back(dealValueList[(i+1)%13][jkk]);
                                    Move mv(TRIPLE_DOUBLE, getValue(i,grade), vc);
                                    if(!InMoves(vMv, vc))
                                        vMv.push_back(mv);
                                    vc.pop_back();
                                }
                                vc.pop_back();
                            }
                            vc.pop_back();
                        } // for jk, i+1
                        vc.pop_back();
                    } // for j, i+1
                    vc.pop_back();
                } // for kk, i
                vc.pop_back();
            } // for jj, i
        } // for size
    } // for i in [0..11]
    return vMv;
}

vector<Move> findTwinTriple(vector<int> &deal, int grade, int dealMap[54], int dealValueMap[13], int dealValueList[13][10]) {
            vector<Move> vMv;
            for(int i=1; i<12; i++) {
                if(dealValueMap[i] >= 2
                 && dealValueMap[i+1] >= 2
                 && dealValueMap[(i+2)%13] >= 2) {
                     int nGrades = dealMap[grade - 1 + 13];
                     vector<int> vc;
                for(int jj=0; jj<dealValueMap[i]-1; jj++) {
                    if(dealValueList[i][jj] == grade - 1 + 13 
                    && nGrades > 0) {
                        nGrades --;
                    }
                    vc.push_back(dealValueList[i][jj]);
                    for(int kk=jj+1; kk<dealValueMap[i]; kk++) {
                    if(dealValueList[i][kk] == grade - 1 + 13 
                    && nGrades > 0) {
                        nGrades --;
                    } else if(dealValueList[i][kk] == grade - 1 + 13)
                           continue; 
                    vc.push_back(dealValueList[i][kk]);
                for(int j=0; j<dealValueMap[i+1]-1; j++) {
                    if(dealValueList[i+1][j] == grade - 1 + 13
                    && nGrades > 0) {
                        nGrades --;
                    } else if(dealValueList[i+1][j] == grade - 1 + 13)
                           continue; 
                    vc.push_back(dealValueList[i+1][j]);
                    for(int jk=j+1; jk<dealValueMap[i+1]; jk++) {
                     if(dealValueList[i+1][jk] == grade - 1 + 13
                    && nGrades > 0) {
                        nGrades --;
                    } else if(dealValueList[i+1][jk] == grade - 1 + 13)
                           continue; 
                     vc.push_back(dealValueList[i+1][jk]);
                    for(int k=0; k<dealValueMap[(i+2)%13]-1; k++){
                        if(dealValueList[(i+2)%13][k] == grade - 1 + 13
                        && nGrades > 0) {
                            nGrades --;
                        }  else if(dealValueList[(i+2)%13][k] == grade - 1 + 13)
                           continue;  
                        vc.push_back(dealValueList[(i+2)%13][k]);
                        for(int ll=k+1; ll<dealValueMap[(i+2)%13]; ll++){
                        if(dealValueList[(i+2)%13][ll] == grade - 1 + 13
                        && nGrades > 0) {
                            nGrades --;
                        }  else if(dealValueList[(i+2)%13][ll] == grade - 1 + 13)
                           continue;  
                        vc.push_back(dealValueList[(i+2)%13][ll]);
                            if(!InMoves(vMv, vc)) {
                                Move mv(TWIN_TRIPLE, getValue(i,grade), vc);
                                vMv.push_back(mv);
                            }
                        vc.pop_back();
                        }
                        vc.pop_back();                                
                       }                           
                        vc.pop_back();
                      } // for jk, i+1
                        vc.pop_back();                     
                    } // for j, i+1
                    vc.pop_back();
                } // for kk, i
                vc.pop_back();
            } // for jj, i
        } // for size
    } // for i in [0..10]
    return vMv;
        }

vector<Move> findTripleDouble(vector<int> deal, int grade,
        int dealMap[54], int dealValueMap[13], int dealValueList[13][10])
        {
            vector<Move> vRet;
            vector<Move> vMv = findTriple(grade, dealValueMap, dealValueList);
            for(int i=0; i<vMv.size(); i++){
                vector<int> nextDeal = deal;
                for(int j=0; j<vMv[i].cards.size(); j++) 
                    removeFromDeal(nextDeal, vMv[i].cards[j]);
                
                // Map to [0...53]
                // Sort as Spades, Hearts, Clubs, Diamonds & Jokers
                int dealMapDouble[54] = {0};
                int dealValueMapDouble[13] = {0};
                int dealValueListDouble[13][10] = {0};
                for(int i=0; i<nextDeal.size(); i++)
                {
                    dealMapDouble[nextDeal[i]] ++;
                    if(nextDeal[i] < 52)
                        dealValueListDouble[nextDeal[i] % 13][dealValueMapDouble[nextDeal[i] % 13] ++] = nextDeal[i];
                }
                // push the heart grade to the tail of dealValueList
                if(dealMap[grade - 1 + 13] > 0) {
                    for(int i=0; i<13; i++) {
                        if(i == (grade - 1 + 13) % 13)
                            continue;
                        for(int j=0; j<dealMapDouble[grade - 1 + 13]; j++)
                            dealValueListDouble[i][dealValueMapDouble[i] ++] = grade - 1 + 13;
                    }
                 }

                vector<Move> vMvDoubles = findDouble(grade, dealMapDouble, dealValueMapDouble, dealValueListDouble);
                if(vMvDoubles.size()>0) {
                    if(vMvDoubles[0].getValue() == vMv[i].getValue())
                        continue;
                    vector<int> vc;
                    for(int k=0; k<vMv[i].cards.size(); k++)
                        vc.push_back(vMv[i].cards[k]);
                    for(int m=0; m<vMvDoubles.size();m++) {
                        for(int n=0; n<vMvDoubles[m].cards.size(); n++)
                            vc.push_back(vMvDoubles[m].cards[n]);
                        vector<int> tp(vc);
                        std::sort(tp.begin(), tp.end());
                        Move mv(TRIPLEDOUBLE, vMv[i].getValue(), tp);
                        if(!InMoves(vRet, tp)) {
                            vRet.push_back(mv);
                        }
                        for(int n=0; n<vMvDoubles[m].cards.size(); n++)
                            vc.pop_back();
                    }
                }
            }
            return vRet;
        }

vector<Move> findNineBomb(vector<int> &deal, int grade,
        int dealMap[54], int dealValueMap[13], int dealValueList[13][10])
        {
            vector<Move> vMv;
   if(deal.size() >= 9) {
         // at least one hearts grade
        if(dealMap[grade-1 + 13] >= 1) {
           for(int i=0; i<13; i++) {
                if(i == grade - 1)
                    break;
                if(dealMap[i] == 2
                   && dealMap[i+13] == 2
                   && dealMap[i+13*2] == 2
                   && dealMap[i+13*3] == 2) {
                    vector<int> vc;
                    // push two hearts
                    vc.push_back(grade - 1 + 13);
                    for(int j=0; j<3; j++) {
                        vc.push_back(i + 13 * j);
                        vc.push_back(i + 13 * j);
                    }
                        Move mv(TEN_BOMB, getValue(i,grade), vc);
                        vMv.push_back(mv);
                   }

           }
        }  
    }
            return vMv;
        }

vector<Move> findTenBomb(vector<int> &deal, int grade,
        int dealMap[54], int dealValueMap[13], int dealValueList[13][10])
        {
         vector<Move> vMv;
       if(deal.size()<10)
            return vMv;
       // Tow hearts grade
        if(dealMap[grade-1 + 13] == 2) 
            for(int i=0; i<13; i++) {
                if(i == grade - 1)
                    break;
                if(dealMap[i] == 2
                   && dealMap[i+13] == 2
                   && dealMap[i+13*2] == 2
                   && dealMap[i+13*3] == 2) {
                    vector<int> vc;
                    // push two hearts
                    vc.push_back(grade - 1 + 13);
                    vc.push_back(grade - 1 + 13);
                    for(int j=0; j<3; j++) {
                        vc.push_back(i + 13 * j);
                        vc.push_back(i + 13 * j);
                    }
                        Move mv(TEN_BOMB, getValue(i,grade), vc);
                        vMv.push_back(mv);
                   }
            }            
            return vMv;
        }

vector<Move> getMoves(vector<int> &deal, int grade)
{
    vector< Move > ret;
    if(!deal.size()) {
        return ret;
    }
    // Map to [0...53]
    // Sort as Spades, Hearts, Clubs, Diamonds & Jokers
    int dealMap[54] = {0};
    int dealMapEx[54] = {0};
    int dealValueMap[13] = {0};
    int dealValueList[13][10] = {0};
    int dealMapList[54][2] = {0};
    for(int i=0; i<deal.size(); i++)
    {
        dealMap[deal[i]] ++;
        if(deal[i] < 52)
            dealValueList[deal[i] % 13][dealValueMap[deal[i] % 13] ++] = deal[i];
        if(!dealMapEx[deal[i]])
            dealMapList[deal[i]][dealMapEx[deal[i]] ++] = deal[i];
    }        
    // push the heart grade to the tail of dealValueList
    if(dealMap[grade - 1 + 13] > 0) {
        for(int i=0; i<13; i++) {
                if(i == (grade - 1 + 13) % 13)
                    continue;
                for(int j=0; j<dealMap[grade - 1 + 13]; j++)
                    dealValueList[i][dealValueMap[i] ++] = grade - 1 + 13; 
        }
        for(int i=0; i<52; i++) {
            if(i == grade - 1 + 13)
                continue;
             dealMapList[i][dealMapEx[i] ++] = grade - 1 + 13; 
        }
    }

    // Find TEN_BOMB
    if(deal.size() >= 10) {
        vector<Move> vMv = findTenBomb(deal, grade, dealMap, dealValueMap, dealValueList);
           for(int i=0; i<vMv.size(); i++){
                    ret.push_back(vMv[i]);
            }
    }

    // FIND NINE_BOMB
    if(deal.size() >= 9) {
        vector<Move> vMv = findNineBomb(deal, grade, dealMap, dealValueMap, dealValueList);
           for(int i=0; i<vMv.size(); i++){
                    ret.push_back(vMv[i]);
            }
    }
    // Find 8 bomb
    if(deal.size() >= 8) {
        vector<Move> vMv = findEightBombs(grade, dealValueMap, dealValueList);
           for(int i=0; i<vMv.size(); i++){
                    ret.push_back(vMv[i]);
            }
    }
    // Find 7 bomb
    if(deal.size() >= 7) {
        vector<Move> vMv = findSevenBombs(grade, dealValueMap, dealValueList);
           for(int i=0; i<vMv.size(); i++){
                    ret.push_back(vMv[i]);
            }
    }
    // Find 6 bomb
    if(deal.size() >= 6) {
        vector<Move> vMv = findSixBombs(grade, dealValueMap, dealValueList);
           for(int i=0; i<vMv.size(); i++){
                    ret.push_back(vMv[i]);
            }
    }
    // Find 5 bomb
    if(deal.size() >= 5) {
        vector<Move> vMv = findFiveBombs(grade, dealValueMap, dealValueList);
           for(int i=0; i<vMv.size(); i++){
                    ret.push_back(vMv[i]);
            }
    }
    // Find 4 bomb
    if(deal.size() >= 4) {
        vector<Move> vMv = findFourBombs(grade, dealValueMap, dealValueList);
           for(int i=0; i<vMv.size(); i++){
                    ret.push_back(vMv[i]);
            }
    }
    // Find Triple
    if(deal.size() >= 3) {
        vector<Move> vMv = findTriple(grade, dealValueMap, dealValueList);
           for(int i=0; i<vMv.size(); i++){
                    ret.push_back(vMv[i]);
            }
    }
    // Find Double
    if(deal.size() >= 2) {
        vector<Move> vMv = findDouble(grade, dealMap, dealValueMap, dealValueList);
           for(int i=0; i<vMv.size(); i++){
                    ret.push_back(vMv[i]);
            }
    }
    // Find Single
    if(deal.size() >= 1) {
        vector<Move> vMv = findSingle(grade, dealMap, dealValueMap, dealValueList);
           for(int i=0; i<vMv.size(); i++){
                    ret.push_back(vMv[i]);
            }
    }
    // Find TWINTRIPLE
    if(deal.size() >= 6) {
        vector<Move> vMv = findTwinTriple(deal, grade, dealMap, dealValueMap, dealValueList);
           for(int i=0; i<vMv.size(); i++){
                    ret.push_back(vMv[i]);
            }
    }
    // Find TRIPLEDOUBLES
    if(deal.size() >= 6) {
        vector<Move> vMv = findTripleDoubles(deal, grade, dealMap, dealValueMap, dealValueList);
           for(int i=0; i<vMv.size(); i++){
                    ret.push_back(vMv[i]);
            }
    }
    // Find TRIPLEDOUBLE
    if(deal.size() >= 5) {
        vector<Move> vMv = findTripleDouble(deal, grade, dealMap, dealValueMap, dealValueList);
           for(int i=0; i<vMv.size(); i++){
                    ret.push_back(vMv[i]);
            }
    }
   // Find SEQUENCER
    if(deal.size() >= 5) {
        vector<Move> vMv = findSequencer(grade, dealMap, dealValueMap, dealValueList);
           for(int i=0; i<vMv.size(); i++){
                    ret.push_back(vMv[i]);
            }
    }
   // Find PURESEUQENCER
    if(deal.size() >= 5) {
        vector<Move> vMv = findPureSequencer(grade, dealMap, dealMapEx, dealMapList);
           for(int i=0; i<vMv.size(); i++){
                    ret.push_back(vMv[i]);
            }
    }
   // Find JokerBomber
    if(deal.size() >= 4) {
        vector<Move> vMv = findJokerBomber(grade, dealMap, dealValueMap, dealValueList);
           for(int i=0; i<vMv.size(); i++){
                    ret.push_back(vMv[i]);
            }
    }
    return ret;
}

map<string, Shape> hashShapes;

string dealStr(const vector<int> deal)
{
    string strOut = "";
    for(int i=0; i<deal.size(); i++){
        char buff[255] = {0};
        sprintf(buff, "%d ", deal[i]);
        strOut += buff;
    }
    return strOut;
}

string dealStrWithBegin(const vector<int> deal, int begin)
{
    string strOut = "";
    for(int i=0; i<deal.size(); i++){
        char buff[255] = {0};
        sprintf(buff, "%d ", deal[i]);
        strOut += buff;
    }
    char beginbuf[33] = {0};
    sprintf(beginbuf, "%d", begin);
    strOut += begin;
    return strOut;
}

const int hash_seed = 0x9e3779b9;
int hash_size = 0x11000000;
std::size_t hashValue(std::vector<int> const& vec) {
    std::size_t seed = vec.size();
    for(auto& i : vec) {
        seed ^= i + hash_seed + (seed << 6) + (seed >> 2);
    }
    return seed % hash_size;
}

Shape* hash_shapes = NULL;

Shape getminShape(vector<int> deal, int grade, int beginning)
{
    Shape ret;
    if(!deal.size()) {
        return ret;
    }
    
    if(deal.size() == 1)
    {
        vector<Move> r;
        vector<int> vc;
        vc.push_back(deal[0]);
        r.push_back(Move(SINGLE, getValue(deal[0],grade), vc));
        ret = Shape(r);
        //        if(!hashShapes.count(dealStr(deal)))
        //            hashShapes[dealStr(deal)] = ret;
        return ret;
    }
    
    sort(deal.begin(), deal.end());
    if(hashShapes.count(dealStrWithBegin(deal, beginning)))
        return hashShapes[dealStrWithBegin(deal, beginning)];
//    vector<int> hashs = deal;
//    hashs.push_back(beginning);
//    Shape sp = hash_shapes[hashValue(hashs)];
//    if(sp.size())
//        return sp;
    // Map to [0...53]
    // Sort as Spades, Hearts, Clubs, Diamonds & Jokers
    int dealMap[54] = {0};
    int dealMapEx[54] = {0};
    int dealValueMap[13] = {0};
    int dealValueList[13][10] = {0};
    int dealMapList[54][2] = {0};
    for(int i=0; i<deal.size(); i++)
    {
        dealMap[deal[i]] ++;
        if(deal[i] < 52)
            dealValueList[deal[i] % 13][dealValueMap[deal[i] % 13] ++] = deal[i];
        if(!dealMapEx[deal[i]])
            dealMapList[deal[i]][dealMapEx[deal[i]] ++] = deal[i];
    }
    // push the heart grade to the tail of dealValueList
    if(dealMap[grade - 1 + 13] > 0) {
        for(int i=0; i<13; i++) {
            if(i == (grade - 1 + 13) % 13)
                continue;
            for(int j=0; j<dealMap[grade - 1 + 13]; j++)
                dealValueList[i][dealValueMap[i] ++] = grade - 1 + 13;
        }
        for(int i=0; i<52; i++) {
            if(i == grade - 1 + 13)
                continue;
            dealMapList[i][dealMapEx[i] ++] = grade - 1 + 13;
        }
    }
    
    // Find TEN_BOMB
    if(deal.size() >= 10
       && beginning >= 10) {
        vector<Move> vMv = findTenBomb(deal, grade, dealMap, dealValueMap, dealValueList);
        for(int i=0; i<vMv.size(); i++){
            vector<int> nextDeal = deal;
            for(int j=0; j<vMv[i].cards.size(); j++)
                removeFromDeal(nextDeal, vMv[i].cards[j]);
            Shape vt = getminShape(nextDeal, grade, 10);
            if(ret.size() && vt.size() >= ret.size() - 1)
                continue;
            Shape sp;
            sp.push_move(vMv[i]);
            sp.concat_shape(vt);
            //sp.sort();
            if(ret.size() && ret.size() > sp.size())
                ret = sp;
            else if(!ret.size())
                ret = sp;
        }
    }
    
    // FIND NINE_BOMB
    if(deal.size() >= 9
       && beginning >= 9) {
        vector<Move> vMv = findNineBomb(deal, grade, dealMap, dealValueMap, dealValueList);
        for(int i=0; i<vMv.size(); i++){
            vector<int> nextDeal = deal;
            for(int j=0; j<vMv[i].cards.size(); j++)
                removeFromDeal(nextDeal, vMv[i].cards[j]);
            Shape vt = getminShape(nextDeal, grade, 9);
            if(ret.size() && vt.size() >= ret.size() - 1)
                continue;
            Shape sp;
            sp.push_move(vMv[i]);
            sp.concat_shape(vt);
            //sp.sort();
            if(ret.size() && ret.size() > sp.size())
                ret = sp;
            else if(!ret.size())
                ret = sp;
        }
    }
    // Find 8 bomb
    if(deal.size() >= 8
       && beginning >= 8) {
        vector<Move> vMv = findEightBombs(grade, dealValueMap, dealValueList);
        for(int i=0; i<vMv.size(); i++){
            vector<int> nextDeal = deal;
            for(int j=0; j<vMv[i].cards.size(); j++)
                removeFromDeal(nextDeal, vMv[i].cards[j]);
            Shape vt = getminShape(nextDeal, grade, 8);
            if(ret.size() && vt.size() >= ret.size() - 1)
                continue;
            Shape sp;
            sp.push_move(vMv[i]);
            sp.concat_shape(vt);
            //sp.sort();
            if(ret.size() && ret.size() > sp.size())
                ret = sp;
            else if(!ret.size())
                ret = sp;
        }
    }
    // Find 7 bomb
    if(deal.size() >= 7
       && beginning >= 7) {
        vector<Move> vMv = findSevenBombs(grade, dealValueMap, dealValueList);
        for(int i=0; i<vMv.size(); i++){
            vector<int> nextDeal = deal;
            for(int j=0; j<vMv[i].cards.size(); j++)
                removeFromDeal(nextDeal, vMv[i].cards[j]);
            Shape vt = getminShape(nextDeal, grade, 7);
            if(ret.size() && vt.size() >= ret.size() - 1)
                continue;
            Shape sp;
            sp.push_move(vMv[i]);
            sp.concat_shape(vt);
            //sp.sort();
            if(ret.size() && ret.size() > sp.size())
                ret = sp;
            else if(!ret.size())
                ret = sp;
        }
    }
    // Find 6 bomb
    if(deal.size() >= 6
       && beginning >= 6) {
        vector<Move> vMv = findSixBombs(grade, dealValueMap, dealValueList);
        for(int i=0; i<vMv.size(); i++){
            vector<int> nextDeal = deal;
            for(int j=0; j<vMv[i].cards.size(); j++)
                removeFromDeal(nextDeal, vMv[i].cards[j]);
            Shape vt = getminShape(nextDeal, grade, 6);
            if(ret.size() && vt.size() >= ret.size() - 1)
                continue;
            Shape sp;
            sp.push_move(vMv[i]);
            sp.concat_shape(vt);
            //sp.sort();
            if(ret.size() && ret.size() > sp.size())
                ret = sp;
            else if(!ret.size())
                ret = sp;
        }
    }
    // Find TWINTRIPLE
    if(deal.size() >= 6
       && beginning >= 6) {
        vector<Move> vMv = findTwinTriple(deal, grade, dealMap, dealValueMap, dealValueList);
        for(int i=0; i<vMv.size(); i++){
            vector<int> nextDeal = deal;
            for(int j=0; j<vMv[i].cards.size(); j++)
                removeFromDeal(nextDeal, vMv[i].cards[j]);
            Shape vt = getminShape(nextDeal, grade, 6);
            if(ret.size() && vt.size() >= ret.size() - 1)
                continue;
            Shape sp;
            sp.push_move(vMv[i]);
            sp.concat_shape(vt);
            //sp.sort();
            if(ret.size() && ret.size() > sp.size())
                ret = sp;
            else if(!ret.size())
                ret = sp;
        }
    }
    // Find TRIPLEDOUBLES
    if(deal.size() >= 6
       && beginning >= 6) {
        vector<Move> vMv = findTripleDoubles(deal, grade, dealMap, dealValueMap, dealValueList);
        for(int i=0; i<vMv.size(); i++){
            vector<int> nextDeal = deal;
            for(int j=0; j<vMv[i].cards.size(); j++)
                removeFromDeal(nextDeal, vMv[i].cards[j]);
            Shape vt = getminShape(nextDeal, grade, 6);
            if(ret.size() && vt.size() >= ret.size() - 1)
                continue;
            Shape sp;
            sp.push_move(vMv[i]);
            sp.concat_shape(vt);
            //sp.sort();
            if(ret.size() && ret.size() > sp.size())
                ret = sp;
            else if(!ret.size())
                ret = sp;
        }
    }
    // Find TRIPLEDOUBLE
    if(deal.size() >= 5
       && beginning >= 5) {
        vector<Move> vMv = findTripleDouble(deal, grade, dealMap, dealValueMap, dealValueList);
        for(int i=0; i<vMv.size(); i++){
            vector<int> nextDeal = deal;
            for(int j=0; j<vMv[i].cards.size(); j++)
                removeFromDeal(nextDeal, vMv[i].cards[j]);
            Shape vt = getminShape(nextDeal, grade, 5);
            if(ret.size() && vt.size() >= ret.size() - 1)
                continue;
            Shape sp;
            sp.push_move(vMv[i]);
            sp.concat_shape(vt);
            //sp.sort();
            if(ret.size() && ret.size() > sp.size())
                ret = sp;
            else if(!ret.size())
                ret = sp;
        }
    }
    // Find SEQUENCER
    if(deal.size() >= 5
       && beginning >= 5) {
        vector<Move> vMv = findSequencer(grade, dealMap, dealValueMap, dealValueList);
        for(int i=0; i<vMv.size(); i++){
            vector<int> nextDeal = deal;
            for(int j=0; j<vMv[i].cards.size(); j++)
                removeFromDeal(nextDeal, vMv[i].cards[j]);
            Shape vt = getminShape(nextDeal, grade, 5);
            if(ret.size() && vt.size() >= ret.size() - 1)
                continue;
            Shape sp;
            sp.push_move(vMv[i]);
            
            sp.concat_shape(vt);
            //sp.sort();
            if(ret.size() && ret.size() > sp.size())
                ret = sp;
            else if(!ret.size())
                ret = sp;
        }
    }
    // Find PURESEUQENCER
    if(deal.size() >= 5
       && beginning >= 5) {
        vector<Move> vMv = findPureSequencer(grade, dealMap, dealMapEx, dealMapList);
        for(int i=0; i<vMv.size(); i++){
            vector<int> nextDeal = deal;
            for(int j=0; j<vMv[i].cards.size(); j++)
                removeFromDeal(nextDeal, vMv[i].cards[j]);
            Shape vt = getminShape(nextDeal, grade, 5);
            if(ret.size() && vt.size() >= ret.size() - 1)
                continue;
            Shape sp;
            sp.push_move(vMv[i]);
            sp.concat_shape(vt);
            //sp.sort();
            if(ret.size() && ret.size() > sp.size())
                ret = sp;
            else if(!ret.size())
                ret = sp;
        }
    }
    // Find 5 bomb
    if(deal.size() >= 5
       && beginning >= 5) {
        vector<Move> vMv = findFiveBombs(grade, dealValueMap, dealValueList);
        for(int i=0; i<vMv.size(); i++){
            vector<int> nextDeal = deal;
            for(int j=0; j<vMv[i].cards.size(); j++)
                removeFromDeal(nextDeal, vMv[i].cards[j]);
            Shape vt = getminShape(nextDeal, grade, 5);
            if(ret.size() && vt.size() >= ret.size() - 1)
                continue;
            Shape sp;
            sp.push_move(vMv[i]);
            sp.concat_shape(vt);
            //sp.sort();
            if(ret.size() && ret.size() > sp.size())
                ret = sp;
            else if(!ret.size())
                ret = sp;
        }
    }
    // Find 4 bomb
    if(deal.size() >= 4
       && beginning >= 4) {
        vector<Move> vMv = findFourBombs(grade, dealValueMap, dealValueList);
        for(int i=0; i<vMv.size(); i++){
            vector<int> nextDeal = deal;
            for(int j=0; j<vMv[i].cards.size(); j++)
                removeFromDeal(nextDeal, vMv[i].cards[j]);
            Shape vt = getminShape(nextDeal, grade, 4);
            if(ret.size() && vt.size() >= ret.size() - 1)
                continue;
            Shape sp;
            sp.push_move(vMv[i]);
            sp.concat_shape(vt);
            //sp.sort();
            if(ret.size() && ret.size() > sp.size())
                ret = sp;
            else if(!ret.size())
                ret = sp;
        }
    }
    // Find JokerBomber
    if(deal.size() >= 4
       && beginning >= 4) {
        vector<Move> vMv = findJokerBomber(grade, dealMap, dealValueMap, dealValueList);
        for(int i=0; i<vMv.size(); i++){
            vector<int> nextDeal = deal;
            for(int j=0; j<vMv[i].cards.size(); j++)
                removeFromDeal(nextDeal, vMv[i].cards[j]);
            Shape vt = getminShape(nextDeal, grade, 4);
            if(ret.size() && vt.size() >= ret.size() - 1)
                continue;
            Shape sp;
            sp.push_move(vMv[i]);
            sp.concat_shape(vt);
            //sp.sort();
            if(ret.size() && ret.size() > sp.size())
                ret = sp;
            else if(!ret.size())
                ret = sp;
        }
    }
    // Find Triple
    if(deal.size() >= 3
       && beginning >= 3) {
        vector<Move> vMv = findTriple(grade, dealValueMap, dealValueList);
        for(int i=0; i<vMv.size(); i++){
            vector<int> nextDeal = deal;
            for(int j=0; j<vMv[i].cards.size(); j++)
                removeFromDeal(nextDeal, vMv[i].cards[j]);
            Shape vt = getminShape(nextDeal, grade, 3);
            if(ret.size() && vt.size() >= ret.size() - 1)
                continue;
            Shape sp;
            sp.push_move(vMv[i]);
            sp.concat_shape(vt);
            //sp.sort();
            if(ret.size() && ret.size() > sp.size())
                ret = sp;
            else if(!ret.size())
                ret = sp;
        }
    }
    // Find Double
    if(deal.size() >= 2
       && beginning >= 2) {
        vector<Move> vMv = findDouble(grade, dealMap, dealValueMap, dealValueList);
        for(int i=0; i<vMv.size(); i++){
            vector<int> nextDeal = deal;
            for(int j=0; j<vMv[i].cards.size(); j++)
                removeFromDeal(nextDeal, vMv[i].cards[j]);
            Shape vt = getminShape(nextDeal, grade, 2);
            if(ret.size() && vt.size() >= ret.size() - 1)
                continue;
            Shape sp;
            sp.push_move(vMv[i]);
            sp.concat_shape(vt);
            //sp.sort();
            if(ret.size() && ret.size() > sp.size()) {
                //                int total = 0;
                //                for(int i=0; i<sp.vMoves.size(); i++){
                //                    total += sp.vMoves[i].cards.size();
                //                }
                //                if(total != deal.size()){
                //                    int ad  = 0;
                //                    ad += 1;
                //                }
                ret = sp;
            } else if(!ret.size())
                ret = sp;
        }
    }
    // Find Single
    if(deal.size() >= 1
       && beginning >= 1) {
        vector<Move> vMv = findSingle(grade, dealMap, dealValueMap, dealValueList);
        for(int i=0; i<vMv.size(); i++){
            vector<int> nextDeal = deal;
            for(int j=0; j<vMv[i].cards.size(); j++)
                removeFromDeal(nextDeal, vMv[i].cards[j]);
            Shape vt = getminShape(nextDeal, grade, 1);
            if(ret.size() && vt.size() >= ret.size() - 1)
                continue;
            Shape sp;
            sp.push_move(vMv[i]);
            sp.concat_shape(vt);
            //sp.sort();
            if(ret.size() && ret.size() > sp.size())
                ret = sp;
            else if(!ret.size())
                ret = sp;
        }
    }
    
    
//    ret.sort();
    if(!hashShapes.count(dealStrWithBegin(deal, beginning)))
        hashShapes[dealStrWithBegin(deal, beginning)] = ret;

//    hash_shapes[hashValue(hashs)] = ret;
//    int total = 0;
//    for(int i=0; i<ret.vMoves.size(); i++){
//        total += ret.vMoves[i].cards.size();
//    }
//    if(total != deal.size()){
//        int ac  = 0;
//        ac += 1;
//    }
    return ret;
}

Shape getminShape(vector<int> deal, int grade)
{

    Shape ret;
    if(!deal.size()) {
        return ret;
    }
    
    if(deal.size() == 1)
    {
        vector<Move> r;
        vector<int> vc;
        vc.push_back(deal[0]);
        r.push_back(Move(SINGLE, getValue(deal[0],grade), vc));
        ret = Shape(r);
//        if(!hashShapes.count(dealStr(deal)))
//            hashShapes[dealStr(deal)] = ret;
        return ret;
    }
    
    sort(deal.begin(), deal.end());
//    int test[] = {4,5,8,19,24,31,43,43,48,49};
//    bool bEqual = true;
//    for(int i=0; i<10; i++){
//        if(test[i] != deal[i]) {
//            bEqual = false;
//            break;
//        }
//    }
//    if(bEqual) {
//        int td = 1;
//        td ++;
//    }
    if(hashShapes.count(dealStr(deal)))
        return hashShapes[dealStr(deal)];
    // Map to [0...53]
    // Sort as Spades, Hearts, Clubs, Diamonds & Jokers
    int dealMap[54] = {0};
    int dealMapEx[54] = {0};
    int dealValueMap[13] = {0};
    int dealValueList[13][10] = {0};
    int dealMapList[54][2] = {0};
    for(int i=0; i<deal.size(); i++)
    {
        dealMap[deal[i]] ++;
        if(deal[i] < 52)
            dealValueList[deal[i] % 13][dealValueMap[deal[i] % 13] ++] = deal[i];
        if(!dealMapEx[deal[i]])
            dealMapList[deal[i]][dealMapEx[deal[i]] ++] = deal[i];
    }
    // push the heart grade to the tail of dealValueList
    if(dealMap[grade - 1 + 13] > 0) {
        for(int i=0; i<13; i++) {
            if(i == (grade - 1 + 13) % 13)
                continue;
            for(int j=0; j<dealMap[grade - 1 + 13]; j++)
                dealValueList[i][dealValueMap[i] ++] = grade - 1 + 13;
        }
        for(int i=0; i<52; i++) {
            if(i == grade - 1 + 13)
                continue;
            dealMapList[i][dealMapEx[i] ++] = grade - 1 + 13;
        }
    }
    
    // Find TEN_BOMB
    if(deal.size() >= 10) {
        vector<Move> vMv = findTenBomb(deal, grade, dealMap, dealValueMap, dealValueList);
        for(int i=0; i<vMv.size(); i++){
            vector<int> nextDeal = deal;
            for(int j=0; j<vMv[i].cards.size(); j++)
                removeFromDeal(nextDeal, vMv[i].cards[j]);
            Shape vt = getminShape(nextDeal, grade);
            if(ret.size() && vt.size() >= ret.size() - 1)
                continue;
            Shape sp;
            sp.push_move(vMv[i]);
            sp.concat_shape(vt);
            //sp.sort();
            if(ret.size() && ret.size() > sp.size())
                ret = sp;
            else if(!ret.size())
                ret = sp;
        }
    }
    
    // FIND NINE_BOMB
    if(deal.size() >= 9) {
        vector<Move> vMv = findNineBomb(deal, grade, dealMap, dealValueMap, dealValueList);
        for(int i=0; i<vMv.size(); i++){
            vector<int> nextDeal = deal;
            for(int j=0; j<vMv[i].cards.size(); j++)
                removeFromDeal(nextDeal, vMv[i].cards[j]);
            Shape vt = getminShape(nextDeal, grade);
            if(ret.size() && vt.size() >= ret.size() - 1)
                continue;
            Shape sp;
            sp.push_move(vMv[i]);
            sp.concat_shape(vt);
            //sp.sort();
            if(ret.size() && ret.size() > sp.size())
                ret = sp;
            else if(!ret.size())
                ret = sp;
        }
    }
    // Find 8 bomb
    if(deal.size() >= 8) {
        vector<Move> vMv = findEightBombs(grade, dealValueMap, dealValueList);
        for(int i=0; i<vMv.size(); i++){
            vector<int> nextDeal = deal;
            for(int j=0; j<vMv[i].cards.size(); j++)
                removeFromDeal(nextDeal, vMv[i].cards[j]);
            Shape vt = getminShape(nextDeal, grade);
            if(ret.size() && vt.size() >= ret.size() - 1)
                continue;
            Shape sp;
            sp.push_move(vMv[i]);
            sp.concat_shape(vt);
            //sp.sort();
            if(ret.size() && ret.size() > sp.size())
                ret = sp;
            else if(!ret.size())
                ret = sp;
        }
    }
    // Find 7 bomb
    if(deal.size() >= 7) {
        vector<Move> vMv = findSevenBombs(grade, dealValueMap, dealValueList);
        for(int i=0; i<vMv.size(); i++){
            vector<int> nextDeal = deal;
            for(int j=0; j<vMv[i].cards.size(); j++)
                removeFromDeal(nextDeal, vMv[i].cards[j]);
            Shape vt = getminShape(nextDeal, grade);
            if(ret.size() && vt.size() >= ret.size() - 1)
                continue;
            Shape sp;
            sp.push_move(vMv[i]);
            sp.concat_shape(vt);
            //sp.sort();
            if(ret.size() && ret.size() > sp.size())
                ret = sp;
            else if(!ret.size())
                ret = sp;
        }
    }
    // Find 6 bomb
    if(deal.size() >= 6) {
        vector<Move> vMv = findSixBombs(grade, dealValueMap, dealValueList);
        for(int i=0; i<vMv.size(); i++){
            vector<int> nextDeal = deal;
            for(int j=0; j<vMv[i].cards.size(); j++)
                removeFromDeal(nextDeal, vMv[i].cards[j]);
            Shape vt = getminShape(nextDeal, grade);
            if(ret.size() && vt.size() >= ret.size() - 1)
                continue;
            Shape sp;
            sp.push_move(vMv[i]);
            sp.concat_shape(vt);
            //sp.sort();
            if(ret.size() && ret.size() > sp.size())
                ret = sp;
            else if(!ret.size())
                ret = sp;
        }
    }
    // Find TWINTRIPLE
    if(deal.size() >= 6) {
        vector<Move> vMv = findTwinTriple(deal, grade, dealMap, dealValueMap, dealValueList);
        for(int i=0; i<vMv.size(); i++){
            vector<int> nextDeal = deal;
            for(int j=0; j<vMv[i].cards.size(); j++)
                removeFromDeal(nextDeal, vMv[i].cards[j]);
            Shape vt = getminShape(nextDeal, grade);
            if(ret.size() && vt.size() >= ret.size() - 1)
                continue;
            Shape sp;
            sp.push_move(vMv[i]);
            sp.concat_shape(vt);
            //sp.sort();
            if(ret.size() && ret.size() > sp.size())
                ret = sp;
            else if(!ret.size())
                ret = sp;
        }
    }
    // Find TRIPLEDOUBLES
    if(deal.size() >= 6) {
        vector<Move> vMv = findTripleDoubles(deal, grade, dealMap, dealValueMap, dealValueList);
        for(int i=0; i<vMv.size(); i++){
            vector<int> nextDeal = deal;
            for(int j=0; j<vMv[i].cards.size(); j++)
                removeFromDeal(nextDeal, vMv[i].cards[j]);
            Shape vt = getminShape(nextDeal, grade);
            if(ret.size() && vt.size() >= ret.size() - 1)
                continue;
            Shape sp;
            sp.push_move(vMv[i]);
            sp.concat_shape(vt);
            //sp.sort();
            if(ret.size() && ret.size() > sp.size())
                ret = sp;
            else if(!ret.size())
                ret = sp;
        }
    }
    // Find TRIPLEDOUBLE
    if(deal.size() >= 5) {
        vector<Move> vMv = findTripleDouble(deal, grade, dealMap, dealValueMap, dealValueList);
        for(int i=0; i<vMv.size(); i++){
            vector<int> nextDeal = deal;
            for(int j=0; j<vMv[i].cards.size(); j++)
                removeFromDeal(nextDeal, vMv[i].cards[j]);
            Shape vt = getminShape(nextDeal, grade);
            if(ret.size() && vt.size() >= ret.size() - 1)
                continue;
            Shape sp;
            sp.push_move(vMv[i]);
            sp.concat_shape(vt);
            //sp.sort();
            if(ret.size() && ret.size() > sp.size())
                ret = sp;
            else if(!ret.size())
                ret = sp;
        }
    }
    // Find SEQUENCER
    if(deal.size() >= 5) {
        vector<Move> vMv = findSequencer(grade, dealMap, dealValueMap, dealValueList);
        for(int i=0; i<vMv.size(); i++){
            vector<int> nextDeal = deal;
            for(int j=0; j<vMv[i].cards.size(); j++)
                removeFromDeal(nextDeal, vMv[i].cards[j]);
            Shape vt = getminShape(nextDeal, grade);
            if(ret.size() && vt.size() >= ret.size() - 1)
                continue;
            Shape sp;
            sp.push_move(vMv[i]);
            
            sp.concat_shape(vt);
            //sp.sort();
            if(ret.size() && ret.size() > sp.size())
                ret = sp;
            else if(!ret.size())
                ret = sp;
        }
    }
    // Find PURESEUQENCER
    if(deal.size() >= 5) {
        vector<Move> vMv = findPureSequencer(grade, dealMap, dealMapEx, dealMapList);
        for(int i=0; i<vMv.size(); i++){
            vector<int> nextDeal = deal;
            for(int j=0; j<vMv[i].cards.size(); j++)
                removeFromDeal(nextDeal, vMv[i].cards[j]);
            Shape vt = getminShape(nextDeal, grade);
            if(ret.size() && vt.size() >= ret.size() - 1)
                continue;
            Shape sp;
            sp.push_move(vMv[i]);
            sp.concat_shape(vt);
            //sp.sort();
            if(ret.size() && ret.size() > sp.size())
                ret = sp;
            else if(!ret.size())
                ret = sp;
        }
    }
    // Find 5 bomb
    if(deal.size() >= 5) {
        vector<Move> vMv = findFiveBombs(grade, dealValueMap, dealValueList);
        for(int i=0; i<vMv.size(); i++){
            vector<int> nextDeal = deal;
            for(int j=0; j<vMv[i].cards.size(); j++)
                removeFromDeal(nextDeal, vMv[i].cards[j]);
            Shape vt = getminShape(nextDeal, grade);
            if(ret.size() && vt.size() >= ret.size() - 1)
                continue;
            Shape sp;
            sp.push_move(vMv[i]);
            sp.concat_shape(vt);
            //sp.sort();
            if(ret.size() && ret.size() > sp.size())
                ret = sp;
            else if(!ret.size())
                ret = sp;
        }
    }
    // Find 4 bomb
    if(deal.size() >= 4) {
        vector<Move> vMv = findFourBombs(grade, dealValueMap, dealValueList);
        for(int i=0; i<vMv.size(); i++){
            vector<int> nextDeal = deal;
            for(int j=0; j<vMv[i].cards.size(); j++)
                removeFromDeal(nextDeal, vMv[i].cards[j]);
            Shape vt = getminShape(nextDeal, grade);
            if(ret.size() && vt.size() >= ret.size() - 1)
                continue;
            Shape sp;
            sp.push_move(vMv[i]);
            sp.concat_shape(vt);
            //sp.sort();
            if(ret.size() && ret.size() > sp.size())
                ret = sp;
            else if(!ret.size())
                ret = sp;
        }
    }
    // Find JokerBomber
    if(deal.size() >= 4) {
        vector<Move> vMv = findJokerBomber(grade, dealMap, dealValueMap, dealValueList);
        for(int i=0; i<vMv.size(); i++){
            vector<int> nextDeal = deal;
            for(int j=0; j<vMv[i].cards.size(); j++)
                removeFromDeal(nextDeal, vMv[i].cards[j]);
            Shape vt = getminShape(nextDeal, grade);
            if(ret.size() && vt.size() >= ret.size() - 1)
                continue;
            Shape sp;
            sp.push_move(vMv[i]);
            sp.concat_shape(vt);
            //sp.sort();
            if(ret.size() && ret.size() > sp.size())
                ret = sp;
            else if(!ret.size())
                ret = sp;
        }
    }
    // Find Triple
    if(deal.size() >= 3) {
        vector<Move> vMv = findTriple(grade, dealValueMap, dealValueList);
        for(int i=0; i<vMv.size(); i++){
            vector<int> nextDeal = deal;
            for(int j=0; j<vMv[i].cards.size(); j++)
                removeFromDeal(nextDeal, vMv[i].cards[j]);
            Shape vt = getminShape(nextDeal, grade);
            if(ret.size() && vt.size() >= ret.size() - 1)
                continue;
            Shape sp;
            sp.push_move(vMv[i]);
            sp.concat_shape(vt);
            //sp.sort();
            if(ret.size() && ret.size() > sp.size())
                ret = sp;
            else if(!ret.size())
                ret = sp;
        }
    }
    // Find Double
    if(deal.size() >= 2) {
        vector<Move> vMv = findDouble(grade, dealMap, dealValueMap, dealValueList);
        for(int i=0; i<vMv.size(); i++){
            vector<int> nextDeal = deal;
            for(int j=0; j<vMv[i].cards.size(); j++)
                removeFromDeal(nextDeal, vMv[i].cards[j]);
            Shape vt = getminShape(nextDeal, grade);
            if(ret.size() && vt.size() >= ret.size() - 1)
                continue;
            Shape sp;
            sp.push_move(vMv[i]);
            sp.concat_shape(vt);
            //sp.sort();
            if(ret.size() && ret.size() > sp.size()) {
//                int total = 0;
//                for(int i=0; i<sp.vMoves.size(); i++){
//                    total += sp.vMoves[i].cards.size();
//                }
//                if(total != deal.size()){
//                    int ad  = 0;
//                    ad += 1;
//                }
                ret = sp;
            } else if(!ret.size())
                ret = sp;
        }
    }
    // Find Single
    if(deal.size() >= 1) {
        vector<Move> vMv = findSingle(grade, dealMap, dealValueMap, dealValueList);
        for(int i=0; i<vMv.size(); i++){
            vector<int> nextDeal = deal;
            for(int j=0; j<vMv[i].cards.size(); j++)
                removeFromDeal(nextDeal, vMv[i].cards[j]);
            Shape vt = getminShape(nextDeal, grade);
            if(ret.size() && vt.size() >= ret.size() - 1)
                continue;
            Shape sp;
            sp.push_move(vMv[i]);
            sp.concat_shape(vt);
            //sp.sort();
            if(ret.size() && ret.size() > sp.size())
                ret = sp;
            else if(!ret.size())
                ret = sp;
        }
    }


    ret.sort();
    if(!hashShapes.count(dealStr(deal)))
        hashShapes[dealStr(deal)] = ret;
    int total = 0;
    for(int i=0; i<ret.vMoves.size(); i++){
        total += ret.vMoves[i].cards.size();
    }
    if(total != deal.size()){
        int ac  = 0;
        ac += 1;
    }
    return ret;
}

vector< Shape > scanmoves(vector<int> deal, int grade)
{
    vector< Shape > ret;
    if(!deal.size()) {
        return ret;
    }
    if(deal.size() == 1)
    {
        vector<Move> r;
        vector<int> vc;
        vc.push_back(deal[0]);
        r.push_back(Move(SINGLE, getValue(deal[0],grade), vc));
        ret.push_back(r);
        return ret;
    }
    // Map to [0...53]
    // Sort as Spades, Hearts, Clubs, Diamonds & Jokers
    int dealMap[54] = {0};
    int dealMapEx[54] = {0};
    int dealValueMap[13] = {0};
    int dealValueList[13][10] = {0};
    int dealMapList[54][2] = {0};
    for(int i=0; i<deal.size(); i++)
    {
        dealMap[deal[i]] ++;
        if(deal[i] < 52)
            dealValueList[deal[i] % 13][dealValueMap[deal[i] % 13] ++] = deal[i];
        if(!dealMapEx[deal[i]])
            dealMapList[deal[i]][dealMapEx[deal[i]] ++] = deal[i];
    }
    // push the heart grade to the tail of dealValueList
    if(dealMap[grade - 1 + 13] > 0) {
        for(int i=0; i<13; i++) {
            if(i == (grade - 1 + 13) % 13)
                continue;
            for(int j=0; j<dealMap[grade - 1 + 13]; j++)
                dealValueList[i][dealValueMap[i] ++] = grade - 1 + 13;
        }
        for(int i=0; i<52; i++) {
            if(i == grade - 1 + 13)
                continue;
            dealMapList[i][dealMapEx[i] ++] = grade - 1 + 13;
        }
    }

    // Find TEN_BOMB
    if(deal.size() >= 10) {
        vector<Move> vMv = findTenBomb(deal, grade, dealMap, dealValueMap, dealValueList);
           for(int i=0; i<vMv.size(); i++){
               vector<int> nextDeal = deal;
                for(int j=0; j<vMv[i].cards.size(); j++) 
                    removeFromDeal(nextDeal, vMv[i].cards[j]);
                vector< Shape > vt = scanmoves(nextDeal, grade);
                for(int k=0; k<vt.size(); k++) {
                    Shape sp;
                    sp.push_move(vMv[i]);
                    sp.concat_shape(vt[k]);
                    sp.sort();
                    ret.push_back(sp);
                }
            }
    }

    // FIND NINE_BOMB
    if(deal.size() >= 9) {
        vector<Move> vMv = findNineBomb(deal, grade, dealMap, dealValueMap, dealValueList);
           for(int i=0; i<vMv.size(); i++){
               vector<int> nextDeal = deal;
               for(int j=0; j<vMv[i].cards.size(); j++)
                   removeFromDeal(nextDeal, vMv[i].cards[j]);
               vector< Shape > vt = scanmoves(nextDeal, grade);
                for(int k=0; k<vt.size(); k++) {
                    Shape sp;
                    sp.push_move(vMv[i]);
                    sp.concat_shape(vt[k]);
                    sp.sort();
                    ret.push_back(sp);
                }
            }
    }
    // Find 8 bomb
    if(deal.size() >= 8) {
        vector<Move> vMv = findEightBombs(grade, dealValueMap, dealValueList);
           for(int i=0; i<vMv.size(); i++){
               vector<int> nextDeal = deal;
               for(int j=0; j<vMv[i].cards.size(); j++)
                   removeFromDeal(nextDeal, vMv[i].cards[j]);
               vector< Shape > vt = scanmoves(nextDeal, grade);
                for(int k=0; k<vt.size(); k++) {
                    Shape sp;
                    sp.push_move(vMv[i]);
                    sp.concat_shape(vt[k]);
                    sp.sort();
                    if(!InShapes(ret, sp))
                        ret.push_back(sp);
                }
            }
    }
    // Find 7 bomb
    if(deal.size() >= 7) {
        vector<Move> vMv = findSevenBombs(grade, dealValueMap, dealValueList);
           for(int i=0; i<vMv.size(); i++){
               vector<int> nextDeal = deal;
               for(int j=0; j<vMv[i].cards.size(); j++)
                   removeFromDeal(nextDeal, vMv[i].cards[j]);
               vector< Shape > vt = scanmoves(nextDeal, grade);
                for(int k=0; k<vt.size(); k++) {
                    Shape sp;
                    sp.push_move(vMv[i]);
                    sp.concat_shape(vt[k]);
                    sp.sort();
                    if(!InShapes(ret, sp))
                        ret.push_back(sp);
                }
            }
    }
    // Find 6 bomb
    if(deal.size() >= 6) {
        vector<Move> vMv = findSixBombs(grade, dealValueMap, dealValueList);
           for(int i=0; i<vMv.size(); i++){
               vector<int> nextDeal = deal;
               for(int j=0; j<vMv[i].cards.size(); j++)
                   removeFromDeal(nextDeal, vMv[i].cards[j]);
               vector< Shape > vt = scanmoves(nextDeal, grade);
                for(int k=0; k<vt.size(); k++) {
                    Shape sp;
                    sp.push_move(vMv[i]);
                    sp.concat_shape(vt[k]);
                    sp.sort();
                    if(!InShapes(ret, sp))
                        ret.push_back(sp);
                }
            }
    }
    // Find 5 bomb
    if(deal.size() >= 5) {
        vector<Move> vMv = findFiveBombs(grade, dealValueMap, dealValueList);
           for(int i=0; i<vMv.size(); i++){
               vector<int> nextDeal = deal;
               for(int j=0; j<vMv[i].cards.size(); j++)
                   removeFromDeal(nextDeal, vMv[i].cards[j]);
               vector< Shape > vt = scanmoves(nextDeal, grade);
                for(int k=0; k<vt.size(); k++) {
                    Shape sp;
                    sp.push_move(vMv[i]);
                    sp.concat_shape(vt[k]);
                    sp.sort();
                    if(!InShapes(ret, sp))
                        ret.push_back(sp);
                }
            }
    }
    // Find 4 bomb
    if(deal.size() >= 4) {
        vector<Move> vMv = findFourBombs(grade, dealValueMap, dealValueList);
           for(int i=0; i<vMv.size(); i++){
               vector<int> nextDeal = deal;
               for(int j=0; j<vMv[i].cards.size(); j++)
                   removeFromDeal(nextDeal, vMv[i].cards[j]);
               vector< Shape > vt = scanmoves(nextDeal, grade);
                for(int k=0; k<vt.size(); k++) {
                    Shape sp;
                    sp.push_move(vMv[i]);
                    sp.concat_shape(vt[k]);
                    sp.sort();
                    if(!InShapes(ret, sp))
                        ret.push_back(sp);
                }
            }
    }
    // Find Triple
    if(deal.size() >= 3) {
        vector<Move> vMv = findTriple(grade, dealValueMap, dealValueList);
           for(int i=0; i<vMv.size(); i++){
               vector<int> nextDeal = deal;
               for(int j=0; j<vMv[i].cards.size(); j++)
                   removeFromDeal(nextDeal, vMv[i].cards[j]);
               vector< Shape > vt = scanmoves(nextDeal, grade);
                for(int k=0; k<vt.size(); k++) {
                    Shape sp;
                    sp.push_move(vMv[i]);
                    sp.concat_shape(vt[k]);
                    sp.sort();
                    if(!InShapes(ret, sp))
                        ret.push_back(sp);
                }
            }
    }
    // Find Double
    if(deal.size() >= 2) {
        vector<Move> vMv = findDouble(grade, dealMap, dealValueMap, dealValueList);
           for(int i=0; i<vMv.size(); i++){
               vector<int> nextDeal = deal;
               for(int j=0; j<vMv[i].cards.size(); j++)
                   removeFromDeal(nextDeal, vMv[i].cards[j]);
               vector< Shape > vt = scanmoves(nextDeal, grade);
                for(int k=0; k<vt.size(); k++) {
                    Shape sp;
                    sp.push_move(vMv[i]);
                    sp.concat_shape(vt[k]);
                    sp.sort();
                    if(!InShapes(ret, sp))
                        ret.push_back(sp);
                }
            }
    }
    // Find Single
    if(deal.size() >= 1) {
        vector<Move> vMv = findSingle(grade, dealMap, dealValueMap, dealValueList);
           for(int i=0; i<vMv.size(); i++){
               vector<int> nextDeal = deal;
               for(int j=0; j<vMv[i].cards.size(); j++)
                   removeFromDeal(nextDeal, vMv[i].cards[j]);
               vector< Shape > vt = scanmoves(nextDeal, grade);
                for(int k=0; k<vt.size(); k++) {
                    Shape sp;
                    sp.push_move(vMv[i]);
                    sp.concat_shape(vt[k]);
                    sp.sort();
                    if(!InShapes(ret, sp))
                        ret.push_back(sp);
                }
            }
    }
    // Find TWINTRIPLE
    if(deal.size() >= 6) {
        vector<Move> vMv = findTwinTriple(deal, grade, dealMap, dealValueMap, dealValueList);
           for(int i=0; i<vMv.size(); i++){
               vector<int> nextDeal = deal;
               for(int j=0; j<vMv[i].cards.size(); j++)
                   removeFromDeal(nextDeal, vMv[i].cards[j]);
               vector< Shape > vt = scanmoves(nextDeal, grade);
                for(int k=0; k<vt.size(); k++) {
                    Shape sp;
                    sp.push_move(vMv[i]);
                    sp.concat_shape(vt[k]);
                    sp.sort();
                    if(!InShapes(ret, sp))
                        ret.push_back(sp);
                }
            }
    }
    // Find TRIPLEDOUBLES
    if(deal.size() >= 6) {
        vector<Move> vMv = findTripleDoubles(deal, grade, dealMap, dealValueMap, dealValueList);
           for(int i=0; i<vMv.size(); i++){
               vector<int> nextDeal = deal;
               for(int j=0; j<vMv[i].cards.size(); j++)
                   removeFromDeal(nextDeal, vMv[i].cards[j]);
               vector< Shape > vt = scanmoves(nextDeal, grade);
                for(int k=0; k<vt.size(); k++) {
                    Shape sp;
                    sp.push_move(vMv[i]);
                    sp.concat_shape(vt[k]);
                    sp.sort();
                    if(!InShapes(ret, sp))
                        ret.push_back(sp);
                }
            }
    }
    // Find TRIPLEDOUBLE
    if(deal.size() >= 5) {
        vector<Move> vMv = findTripleDouble(deal, grade, dealMap, dealValueMap, dealValueList);
           for(int i=0; i<vMv.size(); i++){
               vector<int> nextDeal = deal;
               for(int j=0; j<vMv[i].cards.size(); j++)
                   removeFromDeal(nextDeal, vMv[i].cards[j]);
               vector< Shape > vt = scanmoves(nextDeal, grade);
                for(int k=0; k<vt.size(); k++) {
                    Shape sp;
                    sp.push_move(vMv[i]);
                    sp.concat_shape(vt[k]);
                    sp.sort();
                    if(!InShapes(ret, sp))
                        ret.push_back(sp);
                }
            }
    }
   // Find SEQUENCER
    if(deal.size() >= 5) {
        vector<Move> vMv = findSequencer(grade, dealMap, dealValueMap, dealValueList);
           for(int i=0; i<vMv.size(); i++){
               vector<int> nextDeal = deal;
               for(int j=0; j<vMv[i].cards.size(); j++)
                   removeFromDeal(nextDeal, vMv[i].cards[j]);
               vector< Shape > vt = scanmoves(nextDeal, grade);
                for(int k=0; k<vt.size(); k++) {
                    Shape sp;
                    sp.push_move(vMv[i]);
                    sp.concat_shape(vt[k]);
                    sp.sort();
                    if(!InShapes(ret, sp))
                        ret.push_back(sp);
                }
            }
    }
   // Find PURESEUQENCER
    if(deal.size() >= 5) {
        vector<Move> vMv = findPureSequencer(grade, dealMap, dealMapEx, dealMapList);
           for(int i=0; i<vMv.size(); i++){
               vector<int> nextDeal = deal;
               for(int j=0; j<vMv[i].cards.size(); j++)
                   removeFromDeal(nextDeal, vMv[i].cards[j]);
               vector< Shape > vt = scanmoves(nextDeal, grade);
                for(int k=0; k<vt.size(); k++) {
                    Shape sp;
                    sp.push_move(vMv[i]);
                    sp.concat_shape(vt[k]);
                    sp.sort();
                    if(!InShapes(ret, sp))
                        ret.push_back(sp);
                }
            }
    }
   // Find JokerBomber
    if(deal.size() >= 4) {
        vector<Move> vMv = findJokerBomber(grade, dealMap, dealValueMap, dealValueList);
           for(int i=0; i<vMv.size(); i++){
               vector<int> nextDeal = deal;
               for(int j=0; j<vMv[i].cards.size(); j++)
                   removeFromDeal(nextDeal, vMv[i].cards[j]);
               vector< Shape > vt = scanmoves(nextDeal, grade);
                for(int k=0; k<vt.size(); k++) {
                    Shape sp;
                    sp.push_move(vMv[i]);
                    sp.concat_shape(vt[k]);
                    sp.sort();
                    if(!InShapes(ret, sp))
                        ret.push_back(sp);
                }
//                // restore deal
//                for(int k=0; k<vMv[i].cards.size(); k++)
//                    deal.push_back(vMv[i].cards[k]);
            }
    }
    return ret;
}

void shuffle(vector<int>& wholeDecks)
{
    srand(time(NULL));
    for(int i=wholeDecks.size()-1; i>0; i--) {
        int n = rand() % i;
        int tmp = wholeDecks[i];
        wholeDecks[i] = wholeDecks[n];
        wholeDecks[n] = tmp;
    }
}

void printDeal(vector<int> &deal)
{
    std::sort(deal.begin(), deal.end());
    std::string outStrForS = "S";
    string outStrForH = "H";
    string outStrForC = "C";
    string outStrForD = "D";
    string outJoker = "";
    string outBigJoker = "";
    const char outCard[] = "A23456789TJQK";
    string outStr = "";
    for(int i=0; i<deal.size(); i++) {
        if(deal[i] < 13)
            outStrForS += outCard[deal[i]];
        else if (deal[i] < 26)
            outStrForH += outCard[deal[i]%13];
        else if (deal[i] < 39)
            outStrForC += outCard[deal[i]%13];
        else if (deal[i] < 52)
            outStrForD += outCard[deal[i]%13];
        else if (deal[i] == 52)
            outJoker += "f";
        else if (deal[i] == 53)
            outBigJoker += "F";
    }
    outStr = outStrForS + "\n";
    outStr += outStrForH + "\n";
    outStr += outStrForC + "\n";
    outStr += outStrForD + "\n";
    if(outJoker != "")
        outStr += outJoker + "\n";
    outStr += outBigJoker;
    std::cout << outStr << std::endl;
}

void printMoves(vector<Move> &vMv)
{
    std::string outMoves = "";
    for(int i=0; i<vMv.size(); i++) {
        char buffer[256] = {0};
        sprintf(buffer, "%d: %s\n", i, vMv[i].toStr().c_str());
        outMoves += buffer;
    }
    std::cout << outMoves << std::endl;
}

void printShapes(vector<Shape> &vSp)
{
    std::string outShapes = "";
    for(int i=0; i<vSp.size(); i++) {
        vSp[i].sort();
        char index[255] = {0};
        sprintf(index, "%d: ", i);
        outShapes += index;
        std::string outMoves = "";
        for(int j=0; j<vSp[i].vMoves.size(); j++) {
            char buffer[256] = {0};
            sprintf(buffer, "%s ", vSp[i].vMoves[j].toStr().c_str());
            outMoves += buffer;
        }
        outShapes += outMoves + "\n";
    }
    std::cout << outShapes << std::endl;    
}

void getRandomCards()
{
    vector<int> wholeDecks;
    for(int k=0; k<2; k++)
        for(int i=0; i<54; i++)
            wholeDecks.push_back(i);
    shuffle(wholeDecks);
    vector<int> deal;
//    for(int m=0; m<nMaxCards; m++)
//        deal.push_back(wholeDecks[m]);
    int testDeal[] = {1,2,3,4,5,8,12,14,19,19,24,26,31,33,36,38,38,39,39,41,43,43,46,48,49,51,52};
    //{3,5,8,19,19,24,31,33,36,46,48,49,52};
    //{1,2,3,4,5,8,12,14,19,19,24,26,31,33,36,38,38,39,39,41,43,43,46,48,49,51,52};
    //{3,5,8,19,19,24,31,33,36,46,48,49,52};
    //{1,2,3,4,5,8,12,14,19,19};
    //{3,5,8,19,19,24,31,33,36,46,48,49,52};
    //{1,2,3,4,5,8,12,14,19,19,24,26,31,33,36,38,38,39,39,41,43,43,46,48,49,51,52};
    for(int k=0; k<sizeof(testDeal)/sizeof(testDeal[0]); k++)
        deal.push_back(testDeal[k]);
    printDeal(deal);
    clock_t begin = clock();
    clock_t end;
    double elapsed_secs;
    int grade = rand() % 13 + 1;
    grade = 7;
    std::cout<< "Grade is " << grade << std::endl;
    vector<Move> vMv = getMoves(deal,grade);
    printMoves(vMv);

    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "getMoves run time: " << elapsed_secs << "s" << endl;
    begin = clock();
   
   // hash_shapes = new Shape[hash_size];
    //(Shape*) malloc(sizeof(Shape)*hash_size);
    vector<Shape> vSp;
    Shape sp = getminShape(deal, grade, 10);
    vSp.push_back(sp);
    printShapes(vSp);
  
    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "getminShape run time: " << elapsed_secs << "s" << endl;
    
//    begin = clock();
//    vector<Shape> vSp1;
//    Shape sp1 = getminShape(deal, grade);
//    vSp1.push_back(sp1);
//    printShapes(vSp1);
    
//    vector<Shape> vSp2 = scanmoves(deal, grade);
//    std::sort(vSp2.begin(), vSp2.end(), pred());
//    printShapes(vSp2);
//    end = clock();
//    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
//    cout << "getminShape1 run time: " << elapsed_secs << "s" << endl;
//    if(hash_shapes)
//        free(hash_shapes);
}

void printRound(int nRound, Round round)
{
    cout << nRound << ": " << round.toStr() << endl;
}

void removeMoveFromDeal(vector<int> &deal, Move mv)
{
    for(int i=0; i<mv.cards.size(); i++)
        removeFromDeal(deal, mv.cards[i]);
}

Move getFirstMoveSim(vector<int> &deal, int grade)
{
    Move mv;
    if(deal.size()) {
        vector<Move> mvs = getMoves(deal, grade);
        mv = mvs[rand()%(mvs.size())];
    }
    return mv;
}

Move getFollowMoveSim(vector<int> &deal, int grade, Move mvFirst)
{
    Move mv;
    if(deal.size()) {
        vector<Move> retMv;
        vector<Move> mvs = getMoves(deal, grade);
        for(int i=0; i<mvs.size(); i++){
            if(mvs[i].getType() == mvFirst.getType()
               && mvs[i].getValue() > mvFirst.getValue())
                retMv.push_back(mvs[i]);
            else if(mvs[i].getType() >= FOUR_BOMB
                    && mvs[i].getType() > mvFirst.getType() )
                retMv.push_back(mvs[i]);
        }
        if(retMv.size())
            mv = retMv[rand()%retMv.size()];
    }
    return mv;
}

Move getFirstMove(vector<int> &deal, int grade)
{
    Move mv;
    if(deal.size()) {
        Shape sp = getminShape(deal, grade, 10);
        mv = sp.vMoves[0];
    }
    return mv;
}

Move getFollowMove(vector<int> &deal, int grade, Move mvFirst)
{
    Move mv;
    if(deal.size()) {
        vector<Move> retMv;
        vector<Move> mvs = getMoves(deal, grade);
        for(int i=0; i<mvs.size(); i++){
            if(mvs[i].getType() == mvFirst.getType()
               && mvs[i].getValue() > mvFirst.getValue())
                retMv.push_back(mvs[i]);
            else if(mvs[i].getType() >= FOUR_BOMB
                    && mvs[i].getType() > mvFirst.getType() )
                retMv.push_back(mvs[i]);
        }
        if(retMv.size())
            mv = retMv[0];
    }
    return mv;
}

vector<int> getDealFromStr(string str)
{
    vector<int> deal;
    str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
    const char* chInput = str.c_str();
    char chVal[] = "A23456789TJQK";
    map<char, int> valMap;
    for(int i=0; i<sizeof(chVal)/sizeof(char);i++){
        valMap[chVal[i]] = i;
    }
    unsigned int nsIndex = str.find('S');
    unsigned int nsIndex2 = str.find('H');
    unsigned int nsIndex3 = str.find('C');
    unsigned int nsIndex4 = str.find('D');
    for(unsigned int i=nsIndex+1; i<nsIndex2; i++){
        deal.push_back(valMap[chInput[i]]);
    }

    for(unsigned int i=nsIndex2+1; i<nsIndex3; i++){
        deal.push_back(valMap[chInput[i]]+13);
    }
    for(unsigned int i=nsIndex3+1; i<nsIndex4; i++){
        deal.push_back(valMap[chInput[i]]+13*2);
    }
    for(unsigned int i=nsIndex4+1; i<str.size(); i++){
        if(chInput[i] !='f' && chInput[i] !='F')
            deal.push_back(valMap[chInput[i]]+13*3);
        else if(chInput[i] == 'f')
            deal.push_back(52);
        else if (chInput[i] == 'F')
            deal.push_back(53);
    }
    return deal;
}

int simGame(vector<int> Deals[4], int grade,
            int nfirst, Move mvInput)
{
    int nResult = 0;
    int nFirst = nfirst;
    int nWinList[4] = {0};
    int nWins = 0;
    int nRound = 0;
    int nRoundWin = 0;
    vector<Round> rounds;
   // cout << "Sim move " << mvInput.toStr() << endl;
    char nPos[] = "NWSE";
    Round round;
    int nWinAll = 0;
//    for(int i=0;i<4;i++) {
//        cout<<nPos[i]<<endl;
//        printDeal(Deals[i]);
//        //cout<<endl;
//    }
    Move mv = mvInput;
    while(nWins<3) {
        while(nWinAll<3) {
            Move mv2 = getFollowMoveSim(Deals[(nFirst+1)%4], grade, mv);
            if(mv2.cards.size()) {
                removeMoveFromDeal(Deals[(nFirst+1)%4], mv2);
                nRoundWin = (nFirst+1)%4;
                nWinAll = 0;
                if(Deals[(nFirst+1)%4].size() == 0) {
                    nWinList[nWins++] = (nFirst+1)%4;
                    if(nWins == 3)
                        break;
                }
                round.push_move((nFirst+1)%4, mv2);
            } else {
                mv2 = mv;
                nWinAll ++;
                if(nWinAll == 3)
                    break;
            }
            Move mv3 = getFollowMoveSim(Deals[(nFirst+2)%4], grade, mv2);
            if(mv3.cards.size()) {
                removeMoveFromDeal(Deals[(nFirst+2)%4], mv3);
                nRoundWin = (nFirst+2)%4;
                nWinAll = 0;
                if(Deals[(nFirst+2)%4].size() == 0) {
                    nWinList[nWins++] = (nFirst+2)%4;
                    if(nWins == 3)
                        break;
                }
                round.push_move((nFirst+2)%4, mv3);
            } else {
                mv3 = mv2;
                nWinAll ++;
                if(nWinAll == 3)
                    break;
            }
            Move mv4 = getFollowMoveSim(Deals[(nFirst+3)%4], grade, mv3);
            if(mv4.cards.size()) {
                removeMoveFromDeal(Deals[(nFirst+3)%4], mv4);
                nRoundWin = (nFirst+3)%4;
                nWinAll = 0;
                if(Deals[(nFirst+3)%4].size() == 0) {
                    nWinList[nWins++] = (nFirst+3)%4;
                    if(nWins == 3)
                        break;
                }
                round.push_move((nFirst+3)%4, mv4);
            } else {
                mv4 = mv3;
                nWinAll ++;
                if(nWinAll == 3)
                    break;
            }
            mv = getFollowMoveSim(Deals[nFirst%4], grade, mv4);
            if(mv.cards.size()) {
                removeMoveFromDeal(Deals[nFirst%4], mv);
                nRoundWin = nFirst%4;
                nWinAll = 0;
                if(Deals[nFirst%4].size() == 0) {
                    nWinList[nWins++] = nFirst%4;
                    if(nWins == 3)
                        break;
                }
                round.push_move(nFirst%4, mv);
            } else {
                mv = mv4;
                nWinAll ++;
                if(nWinAll == 3)
                    break;
            }
        }
        
        rounds.push_back(round);
        // print Round info
       // printRound(nRound, rounds[nRound++]);
        nFirst = nRoundWin;
        
        // next round
        nWinAll = 0;
//        for(int i=0;i<4;i++) {
//            cout<<nPos[i]<<endl;
//            printDeal(Deals[i]);
//            //cout<<endl;
//        }
        round.clear();
        if(!Deals[nFirst%4].size()) {
            nFirst = ((nFirst % 4) + 2) % 4;
            if(!Deals[nFirst%4].size())
                nFirst = (nFirst + 1) % 4;
        }
        mv = getFirstMoveSim(Deals[nFirst%4], grade); //Sim
        removeMoveFromDeal(Deals[nFirst%4], mv);
        if(mv.cards.size()) {
            round.push_move(nFirst%4, mv);
            nRoundWin = nFirst%4;
            nWinAll = 0;
        }
        if(Deals[nFirst%4].size() == 0) {
            nWinList[nWins++] = nFirst%4;
            if(nWins == 3)
                break;
        }
        
    }
    // Phase 3: Result
    if( (nWinList[0] == nfirst && nWinList[1] == (nfirst+2)%4)
       || (nWinList[0] == (nfirst+2)%4 && nWinList[1] == nfirst) )
        nResult = 3;
    else if( (nWinList[0] == nfirst && nWinList[2] == (nfirst+2)%4)
            || (nWinList[0] == (nfirst+2)%4 && nWinList[2] == nfirst) )
        nResult = 2;
    else if( nWinList[0] == nfirst
            || nWinList[0] == (nfirst+2)%4 )
        nResult = 1;
    else if( (nWinList[0] == (nfirst+1)%4 && nWinList[1] == (nfirst+3)%4)
            || (nWinList[0] == (nfirst+3)%4 && nWinList[1] == (nfirst+1)%4) )
        nResult = -3;
    else if( (nWinList[0] == (nfirst+1)%4 && nWinList[2] == (nfirst+3)%4)
            || (nWinList[0] == (nfirst+3)%4 && nWinList[2] == (nfirst+1)%4) )
        nResult = -2;
    else
        nResult = -1;
//    char chPos[] = "NWSE";
//    cout << chPos[nWinList[0]] << " " << chPos[nWinList[1]] << " " << chPos[nWinList[2]] << endl;
    return nResult;
}

int simGame(vector<int> Deals[4], int grade, int nfirst)
{
    int nResult = 0;
    int nFirst = nfirst;
    int nWinList[4] = {0};
    int nWins = 0;
    int nRound = 0;
    int nRoundWin = 0;
    vector<Round> rounds;
    char nPos[] = "NWSE";
    while(nWins<3) {
        for(int i=0;i<4;i++) {
            cout<<nPos[i]<<endl;
            printDeal(Deals[i]);
            //cout<<endl;
        }
        if(!Deals[nFirst%4].size()) {
            nFirst = ((nFirst % 4) + 2) % 4;
            if(!Deals[nFirst%4].size())
                nFirst = (nFirst + 1) % 4;
        }
        Move mv = getFirstMove(Deals[nFirst%4], grade); //Sim
        removeMoveFromDeal(Deals[nFirst%4], mv);
        Round round;
        int nWinAll = 0;
        if(mv.cards.size()) {
            round.push_move(nFirst%4, mv);
            nRoundWin = nFirst%4;
            nWinAll = 0;
        }
        if(Deals[nFirst%4].size() == 0) {
            nWinList[nWins++] = nFirst%4;
            if(nWins == 3)
                break;
        }

        while(nWinAll<3) {
            Move mv2 = getFollowMoveSim(Deals[(nFirst+1)%4], grade, mv);
            if(mv2.cards.size()) {
                removeMoveFromDeal(Deals[(nFirst+1)%4], mv2);
                nRoundWin = (nFirst+1)%4;
                nWinAll = 0;
                if(Deals[(nFirst+1)%4].size() == 0) {
                    nWinList[nWins++] = (nFirst+1)%4;
                    if(nWins == 3)
                        break;
                }
                round.push_move((nFirst+1)%4, mv2);
            } else {
                mv2 = mv;
                nWinAll ++;
                if(nWinAll == 3)
                    break;
            }
            Move mv3 = getFollowMoveSim(Deals[(nFirst+2)%4], grade, mv2);
            if(mv3.cards.size()) {
                removeMoveFromDeal(Deals[(nFirst+2)%4], mv3);
                nRoundWin = (nFirst+2)%4;
                nWinAll = 0;
                if(Deals[(nFirst+2)%4].size() == 0) {
                    nWinList[nWins++] = (nFirst+2)%4;
                    if(nWins == 3)
                        break;
                }
                round.push_move((nFirst+2)%4, mv3);
            } else {
                mv3 = mv2;
                nWinAll ++;
                if(nWinAll == 3)
                    break;
            }
            Move mv4 = getFollowMoveSim(Deals[(nFirst+3)%4], grade, mv3);
            if(mv4.cards.size()) {
                removeMoveFromDeal(Deals[(nFirst+3)%4], mv4);
                nRoundWin = (nFirst+3)%4;
                nWinAll = 0;
                if(Deals[(nFirst+3)%4].size() == 0) {
                    nWinList[nWins++] = (nFirst+3)%4;
                    if(nWins == 3)
                        break;
                }
                round.push_move((nFirst+3)%4, mv4);
            } else {
                mv4 = mv3;
                nWinAll ++;
                if(nWinAll == 3)
                    break;
            }
            mv = getFollowMoveSim(Deals[nFirst%4], grade, mv4);
            if(mv.cards.size()) {
                removeMoveFromDeal(Deals[nFirst%4], mv);
                nRoundWin = nFirst%4;
                nWinAll = 0;
                if(Deals[nFirst%4].size() == 0) {
                    nWinList[nWins++] = nFirst%4;
                    if(nWins == 3)
                        break;
                }
                round.push_move(nFirst%4, mv);
            } else {
                mv = mv4;
                nWinAll ++;
                if(nWinAll == 3)
                    break;
            }
        }
        rounds.push_back(round);

        // print Round info
        printRound(nRound, rounds[nRound++]);
        nFirst = nRoundWin;
    }
    // Phase 3: Result
    if( (nWinList[0] == nfirst && nWinList[1] == (nfirst+2)%4)
       || (nWinList[0] == (nfirst+2)%4 && nWinList[1] == nfirst) )
        nResult = 3;
    else if( (nWinList[0] == nfirst && nWinList[2] == (nfirst+2)%4)
            || (nWinList[0] == (nfirst+2)%4 && nWinList[2] == nfirst) )
        nResult = 2;
    else if( nWinList[0] == nfirst
            || nWinList[0] == (nfirst+2)%4 )
        nResult = 1;
    else if( (nWinList[0] == (nfirst+1)%4 && nWinList[1] == (nfirst+3)%4)
            || (nWinList[0] == (nfirst+3)%4 && nWinList[1] == (nfirst+1)%4) )
        nResult = -3;
    else if( (nWinList[0] == (nfirst+1)%4 && nWinList[2] == (nfirst+3)%4)
            || (nWinList[0] == (nfirst+3)%4 && nWinList[2] == (nfirst+1)%4) )
        nResult = -2;
    else
        nResult = -1;
    char chPos[] = "NWSE";
    cout << chPos[nWinList[0]] << " " << chPos[nWinList[1]] << " " << chPos[nWinList[2]] << endl;
    return nResult;
}

void testSimGame()
{
    int nCards = nMaxCards;
    // Phase 1: Get cards
    // Shuffle cards
    vector<int> wholeDecks;
    for(int k=0; k<2; k++)
        for(int i=0; i<54; i++)
            wholeDecks.push_back(i);
    shuffle(wholeDecks);
    vector<int> Deals[4];
    for(int m=0; m<nCards; m++)
        Deals[0].push_back(wholeDecks[m]);
    for(int m=nCards; m<2*nCards; m++)
        Deals[1].push_back(wholeDecks[m]);
    for(int m=2*nCards; m<3*nCards; m++)
        Deals[2].push_back(wholeDecks[m]);
    for(int m=3*nCards; m<4*nCards; m++)
        Deals[3].push_back(wholeDecks[m]);
    
//    Deals[0] = getDealFromStr("SA34578H39C6DA46JKf");
//    Deals[1] = getDealFromStr("SA225H88C347KDA34fF");
//    Deals[2] = getDealFromStr("S3699KH567C29QD56TQ");
//    Deals[3] = getDealFromStr("SH2349KCA357TD2788J");
    // Phase 2: Play
    int grade = rand() % 13 + 1;
  //  grade = 3;
    char chGrade[] = "A23456789TJQK";
    cout << "Grade is " << chGrade[grade-1] << endl;
    int nfirst = 2;
    char chPos[] = "NWSE";
    cout << "First is " << chPos[nfirst] << endl;
    clock_t begin = clock();
//    int nres = simGame(Deals, grade, nfirst);
//    cout << "result is " << nres << endl;
    vector<Round> rounds;
    Move mv = getFirstMove(Deals[nfirst], grade, rounds, nfirst);
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "sim run time: " << elapsed_secs << "s" << endl;
    vector<Move> mvs;
    mvs.push_back(mv);
    printMoves(mvs);
}

void SimulateGame()
{
    int nCards = 5;//nMaxCards;
    // Phase 1: Get cards
    // Shuffle cards
    vector<int> wholeDecks;
    for(int k=0; k<2; k++)
        for(int i=0; i<54; i++)
            wholeDecks.push_back(i);
    shuffle(wholeDecks);
    vector<int> Deals[4];
    for(int m=0; m<nCards; m++)
        Deals[0].push_back(wholeDecks[m]);
    for(int m=nCards; m<2*nCards; m++)
        Deals[1].push_back(wholeDecks[m]);    
    for(int m=2*nCards; m<3*nCards; m++)
        Deals[2].push_back(wholeDecks[m]);
    for(int m=3*nCards; m<4*nCards; m++)
        Deals[3].push_back(wholeDecks[m]);

//    Deals[0] = getDealFromStr("STJQKAHTJQKACTJQKAD");
//    Deals[1] = getDealFromStr("SJQKAHTJQKACDQQKKAA");
//    Deals[2] = getDealFromStr("SA2345HA2345CA2345D");
//    Deals[3] = getDealFromStr("S35689JH6C244TD259T");
    // Phase 2: Play
     int grade = rand() % 13 + 1;
//    grade = 6;
    char chGrade[] = "A23456789TJQK";
    cout << "Grade is " << chGrade[grade-1] << endl;
     int nResult = 0;
     int nFirst = 0;
     int nWinList[4] = {0};
     int nWins = 0;
     int nRound = 0;
     vector<Round> rounds;
     char nPos[] = "NWSE";
    int nRoundWin = 0;
     while(nWins<3) {
         for(int i=0;i<4;i++) {
             cout<<nPos[i]<<endl;
            printDeal(Deals[i]);
             //cout<<endl;
         }
         if(!Deals[nFirst%4].size()) {
             nFirst = ((nFirst % 4) + 2) % 4;
             if(!Deals[nFirst%4].size())
                 nFirst = (nFirst + 1) % 4;
         }
        Move mv = getFirstMoveSim(Deals[nFirst%4], grade);
        removeMoveFromDeal(Deals[nFirst%4], mv);
         Round round;
         int nWinAll = 0;
         if(mv.cards.size()) {
             round.push_move(nFirst%4, mv);
             nRoundWin = nFirst%4;
             nWinAll = 0;
         }
         if(Deals[nFirst%4].size() == 0) {
            nWinList[nWins++] = nFirst%4;
            if(nWins == 3)
                break;
         }
         while(nWinAll < 3) {
             Move mv2 = getFollowMoveSim(Deals[(nFirst+1)%4], grade, mv);
             if(mv2.cards.size()) {
                 removeMoveFromDeal(Deals[(nFirst+1)%4], mv2);
                 nRoundWin = (nFirst+1)%4;
                 if(Deals[(nFirst+1)%4].size() == 0) {
                     nWinList[nWins++] = (nFirst+1)%4;
                     if(nWins == 3)
                         break;
                 }
                 nWinAll = 0;
                 round.push_move((nFirst+1)%4, mv2);
             } else {
                 mv2 = mv;
                 nWinAll ++;
                 if(nWinAll == 3)
                     break;
             }
             Move mv3 = getFollowMoveSim(Deals[(nFirst+2)%4], grade, mv2);
             if(mv3.cards.size()) {
                 removeMoveFromDeal(Deals[(nFirst+2)%4], mv3);
                 nRoundWin = (nFirst+2)%4;
                 if(Deals[(nFirst+2)%4].size() == 0) {
                     nWinList[nWins++] = (nFirst+2)%4;
                     if(nWins == 3)
                         break;
                 }
                 nWinAll = 0;
                 round.push_move((nFirst+2)%4, mv3);
             } else {
                 mv3 = mv2;
                 nWinAll ++;
                 if(nWinAll == 3)
                     break;
             }
             Move mv4 = getFollowMoveSim(Deals[(nFirst+3)%4], grade, mv3);
             if(mv4.cards.size()) {
                 removeMoveFromDeal(Deals[(nFirst+3)%4], mv4);
                 nRoundWin = (nFirst+3)%4;
                 if(Deals[(nFirst+3)%4].size() == 0) {
                     nWinList[nWins++] = (nFirst+3)%4;
                     if(nWins == 3)
                         break;
                 }
                 nWinAll = 0;
                 round.push_move((nFirst+3)%4, mv4);
             } else {
                 mv4 = mv3;
                 nWinAll ++;
                 if(nWinAll == 3)
                     break;
             }
             mv = getFollowMoveSim(Deals[nFirst%4], grade, mv4);
             if(mv.cards.size()) {
                 removeMoveFromDeal(Deals[nFirst%4], mv);
                 nRoundWin = nFirst%4;
                 nWinAll = 0;
                 if(Deals[nFirst%4].size() == 0) {
                     nWinList[nWins++] = nFirst%4;
                     if(nWins == 3)
                         break;
                 }
                 round.push_move(nFirst%4, mv);
             } else {
                 mv = mv4;
                 nWinAll ++;
                 if(nWinAll == 3)
                     break;
             }
         }
         rounds.push_back(round);

        // print Round info
        printRound(nRound, rounds[nRound++]);

        nFirst = nRoundWin;
     }
    // Phase 3: Result
    if( (nWinList[0] == 0 && nWinList[1] == 2)
    || (nWinList[0] == 2 && nWinList[1] == 0) )
        nResult = 3;
    else if( (nWinList[0] == 0 && nWinList[2] == 2)
    || (nWinList[0] == 2 && nWinList[2] == 0) )
        nResult = 2;
    else if( nWinList[0] == 0
    || nWinList[0] == 2 )
        nResult = 1;
    else if( (nWinList[0] == 1 && nWinList[1] == 3)
    || (nWinList[0] == 3 && nWinList[1] == 1) )
        nResult = -3; 
    else if( (nWinList[0] == 1 && nWinList[2] == 3)
    || (nWinList[0] == 3 && nWinList[2] == 1) )
        nResult = -2;
    else
        nResult = -1;
    char chPos[] = "NWSE";
    cout << chPos[nWinList[0]] << " " << chPos[nWinList[1]] << " " << chPos[nWinList[2]] << endl;
    cout << "Finished, result is " << nResult << endl;
}

vector<int> deals[4];

vector<int>* simDeals(vector<int> wholeDecks, int nPosMoves[4],
                      vector<int> deal, int nPos)
{
    deals[nPos%4] = deal;
    shuffle(wholeDecks);
    int n = 0;
    for(int i=0; i<4; i++) {
        if(i==nPos)
            continue;
        for(int j=0; j<nPosMoves[i]; j++)
            deals[i].push_back(wholeDecks[n++]);
    }
    return deals;
}


Move getFirstMove(vector<int> &deal, int grade,
                  const vector<Round> &rounds, int nPos)
{
    Move mv;
    vector<Move> vMvs;
    if(deal.size()) {
        Shape sp = getminShape(deal, grade, 10);
        mv = sp.vMoves[0];
        vector<Move> mvs = getMoves(deal, grade);
        vMvs.push_back(mv);
        for(int k=0; k<mvs.size(); k++) {
            if(!InMoves(vMvs, mvs[k].cards))
                vMvs.push_back(mvs[k]);
        }
    }
    vector<int> wholeDecks;
    for(int k=0; k<2; k++)
        for(int i=0; i<54; i++)
            wholeDecks.push_back(i);
    int nPosMoves[4] = {27,27,27,27};
    for(int np=0; np<4; np++)
        nPosMoves[np] = nMaxCards;
    for(int i=0; i<rounds.size(); i++){
        for(int j=0; j<rounds[j].vMoves.size(); j++){
            removeMoveFromDeal(wholeDecks, rounds[i].vMoves[j].mv);
            nPosMoves[rounds[i].vMoves[j].nPos] -= rounds[i].vMoves[j].mv.cards.size();
        }
    }
    float fMaxValue = -10.0f;
    int iMax = 0;
    int nSims = nMaxSims;
    for(int i=0; i<vMvs.size(); i++) {
        int nRes = 0;
        for(int m=0; m<nSims; m++) {
            vector<int>* deals = simDeals(wholeDecks, nPosMoves, deal, nPos);
            removeMoveFromDeal(deals[nPos], vMvs[i]);
            nRes += simGame(deals, grade, nPos, vMvs[i]);
            //free(deals);
        }
        float fSimRes = nRes/(float)nSims;
        if(fSimRes > fMaxValue) {
            iMax = i;
            fMaxValue = fSimRes;
        }
    }
    if(vMvs.size()) {
        mv = vMvs[iMax];
        cout << fMaxValue << endl;
    }
    return mv;
}

Move getFollowMove(vector<int> &deal, int grade,
                   Move mvFirst, const vector<Round> &rounds, int nPos)
{
    Move mv;
    vector<Move> retMv;
    if(deal.size()) {
        vector<Move> mvs = getMoves(deal, grade);
        for(int i=0; i<mvs.size(); i++){
            if(mvs[i].getType() == mvFirst.getType()
               && mvs[i].getValue() > mvFirst.getValue())
                retMv.push_back(mvs[i]);
            else if(mvs[i].getType() >= FOUR_BOMB
                    && mvs[i].getType() > mvFirst.getType())
                retMv.push_back(mvs[i]);
        }
        if(retMv.size())
            mv = retMv[0];
    }
    vector<int> wholeDecks;
    for(int k=0; k<2; k++)
        for(int i=0; i<54; i++)
            wholeDecks.push_back(i);
    int nPosMoves[4] = {27,27,27,27};
    for(int i=0; i<rounds.size(); i++){
        for(int j=0; j<rounds[j].vMoves.size(); j++){
            removeMoveFromDeal(wholeDecks, rounds[i].vMoves[j].mv);
            nPosMoves[rounds[i].vMoves[j].nPos] -= rounds[i].vMoves[j].mv.cards.size();
        }
    }
    float fMaxValue = -10.0f;
    int iMax = 0;
    int nSims = nMaxSims;
    for(int i=0; i<retMv.size(); i++) {
        int nRes = 0;
        for(int m=0; m<nSims; m++) {
            vector<int>* deals = simDeals(wholeDecks, nPosMoves, deal, nPos);
            removeMoveFromDeal(deals[nPos], retMv[i]);
            nRes += simGame(deals, grade, nPos, retMv[i]);
            //free(deals);
        }
        float fSimRes = nRes/(float)nSims;
        if(fSimRes > fMaxValue) {
            iMax = i;
            fMaxValue = fSimRes;
        }
    }
    if(retMv.size())
        mv = retMv[iMax];
    return mv;
}
