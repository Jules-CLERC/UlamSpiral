#include <iostream>
#include <vector>

using namespace std;

typedef vector <char> CVLine; // un type représentant une ligne de la grille
typedef vector <CVLine> CMatrix; // un type représentant la grille
typedef pair <unsigned, unsigned> CExtract; // un type représentant une coordonnée dans la grille

void ShowMat(CMatrix & Mat)
{
    for (unsigned y(0); y < Mat.size(); y++)
    {
        for (unsigned x(0); x < Mat[y].size(); x++)
        {
            if (Mat[y][x] == '1')
            {
                cout << "\033[44m \033[0m";
                cout << "\033[44m \033[0m";
            }
            else
            {
                cout << "\033[46m \033[0m";
                cout << "\033[46m \033[0m";
            }
        }
    cout << endl;
    }
}

void CreateSpirale(unsigned N, vector<unsigned> TabRes)
{
    //on créer la matrice d'ordre N
    CMatrix Mat;
    Mat.resize(N);
    for (unsigned i(0); i < Mat.size(); i++)
    {
        Mat[i].resize(N);
    }
    //on remplit la matrice représenté par un 0
    for (unsigned y(0); y < Mat.size(); y++)
    {
        for (unsigned x(0); x < Mat[y].size(); x++)
        {
            Mat[y][x] = '0';
        }
    }
    //on démarre la création de la spirale
    pair<unsigned, unsigned> Pos;
    if (N%2 == 0)
    {
        Pos.first = N/2;
        Pos.second = N/2 - 1;
    }
    else
    {
        Pos.first = (N - 1)/2;
        Pos.second = Pos.first;
    }
    unsigned NbPremierMin = 0;
    unsigned dir = 0;
    unsigned cpt = 0;
    unsigned cptDir = 1;
    unsigned cpt2 = 0;
    for (unsigned i = 1; i < N*N + 1; i++)
    {
        //on verifie si i est un nombre premier
        //si c'est le cas, la case prend la valeur 1 sinon elle garde la valeur 0
        if (TabRes[NbPremierMin] == i)
        {
            Mat[Pos.first][Pos.second] = '1';
            NbPremierMin++;
        }
        if (dir % 4 == 0) //aller a droite
        {
            Pos.second++;
        }
        else if (dir % 4 == 1) //aller en haut
        {
            Pos.first--;
        }
        else if (dir % 4 == 2) //aller a gauche
        {
            Pos.second--;
        }
        else //aller en bas
        {
            Pos.first++;
        }
        //ces compteurs permettent le deplacement de l'extracteur dans la spirale
        cpt++;
        if (cpt == cptDir)
        {
            cpt = 0;
            cpt2++;
            dir++;
            if (cpt2 == 2)
            {
                cpt2 = 0;
                cptDir++;
            }
        }
    }
    ShowMat(Mat);
}

void ShowVector(vector<unsigned> Tab)
{
    for (unsigned i = 0; i < Tab.size(); i++)
    {
        cout << Tab[i] << endl;
    }
}

bool EstPremier(unsigned Number, vector<unsigned> TabRes)
{
    bool var = true;
    for (unsigned cpt = 0; cpt < TabRes.size() - 1; cpt++)
    {
        if (Number % TabRes[cpt] == 0)
        {
            var = false;
            break;
        }
    }
    return var;
}

int main()
{
    //dans un premier temps : entrer la taille N de la matrice
    cout << "saisir la taille N de la matrice souhaitée" << endl;
    unsigned N;
    cin >> N;
    //on génère un tableau avec tous les nombres compris entre [ 1 ; N*N ]
    vector <unsigned> TabUnsigned;
    TabUnsigned.resize(N*N);
    for (unsigned i = 1; i < N*N + 1; i++)
    {
        TabUnsigned[i - 1] = i;
    }
    //desormais on doit ajouter dans un second tableau les nombres premiers du tableau précédent
    vector <unsigned> TabRes;
    TabRes.resize(1);
    TabRes[0] = 2;
    for (unsigned j = 3; j < TabUnsigned.size() - 1; j++)
    {
        if (EstPremier(j, TabRes) == true)
        {
            TabRes.resize(TabRes.size() + 1);
            TabRes[TabRes.size() - 1] = j;
            //il ne peut pas y avoir deux nombres premiers à la suite
            j++;
        }
    }
    //maintenant on possède un tableau contenant tous les nombres premiers compris entre [1 ; N*N]
    //il faut maintenant créer une matrice servant de spirale
    CreateSpirale(N, TabRes);
}
