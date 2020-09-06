#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <math.h>
#include<ctype.h>
using namespace std;
bool isLetterValid(string);
bool isLetterValid2(string);
bool isInputDigit(string);
int letterToIndex(string);
void addition(string, string);
void subtraction(string, string);
void transpose(string);
void multiply(string, string);
void multiply_byNum(string, float);
void divide(string, string);
float determinant(vector<vector<float>>, int);
vector<vector<float>> transpose_vector(vector<vector<float>>);
vector<vector<float>> multiply_byNum_vector(vector<vector<float>>, float);
vector<vector<float>> cofactor(vector<vector<float>>);
void inverse(vector<vector<float> >);
vector<vector<float> > GetInverse(vector<vector<float> >);

vector<float> GetElements(string mat) {
    string element;
    vector<float> elements;

    regex re(R"([-]?\d+[.]?([0-9]+)?)");
    //regex re(R"([-]?\d+.\d+)");

    smatch match;
    int i = 1;
    while (regex_search(mat, match, re)) {
        element = match.str(0);
        elements.push_back(stof(element));
        i++;
        mat = match.suffix().str();
    }
    return elements;
}

int getRows(string mat) {
    int c = 1;
    for (int i = 0; i < mat.length(); i++)
    {
        if (mat[i] == ';')
        {
            c++;
        }
    }
    return c;
}

int getColumns(string mat) {
    int c = 0;
    for (int i = 0; i < mat.length(); ++i) {
        if (mat[i] == ';') {
            c++;
        }
    }
    if (c != 0) {
        size_t pos = mat.find(";");
        mat = mat.substr(0, pos + 1);
        vector<float> elements = GetElements(mat);
        return elements.size();
    }
    else {
        vector<float> a = GetElements(mat);
        return a.size();
    }
}

vector<vector<float> > GetMatrix(string mat, int rows, int cols)
{
    vector<float> elements = GetElements(mat);
    vector<vector<float> > v(rows);

    for (int i = 0; i < rows; i++)
    {
        v[i] = vector<float>(cols);
        for (int j = 0; j < cols; j++)
        {
            v[i][j] = elements[i * cols + j];
        }
    }
    return v;
}

vector<vector<float> > GetMatrix(vector<float> elements, int rows, int cols)
{
    vector<vector<float> > v(rows);

    for (int i = 0; i < rows; i++)
    {
        v[i] = vector<float>(cols);
        for (int j = 0; j < cols; j++)
        {
            v[i][j] = elements[i * cols + j];
        }
    }
    return v;
}

vector<vector<float> > GetMatrix(int rows, int cols)
{
    vector<vector<float> > v(rows);

    for (int i = 0; i < rows; i++)
    {
        v[i] = vector<float>(cols);
        for (int j = 0; j < cols; j++)
        {
            v[i][j] = 0;
        }
    }
    return v;
}

void PrintMatrix(vector<vector<float> > mat) {

    for (int i = 0; i < mat.size(); i++)
    {
        for (int j = 0; j < mat[i].size(); j++)
        {
            cout << mat[i][j] << '\t';
        }
        cout << endl;
    }
}

string vectorString(vector<vector<float>> vector) {
    string matrx;
    string element;
    for (int i = 0; i < vector.size(); i++)
    {
        for (int j = 0; j < vector[i].size(); j++)
        {
            element = to_string(vector[i][j]);
            matrx.append(element);
            matrx.append(" ");
        }
        matrx.append(";");
    }
    matrx.pop_back();
    return matrx;
}
bool validMatrix(string mat)
{
    int rows = getRows(mat);
    int cols = getColumns(mat);
    vector<float> elm = GetElements(mat);
    for (int i = 0; i < mat.length(); i++)
    {
        if (isalpha(mat[i]))
        {
            return false;
        }
    }
    if (elm.size() != rows * cols)
    {
        return false;
    }
    return true;
}



string matrices[27];
int n = 0;

int main()
{

    cout << "Welcome, \nThis is a matrix calculator that can do a lot of operations with a lot of options." << endl;
    cout << "To enter Matrices, Enter it like following Examples:\n    [1 2 3 ; 4 5 6 ; 7 8 9] ------ [5 2 3 ; 7 8 1] -->> Like MatLab syntax." << endl;
    cout << "To use your result matrix in another operation just type  \"ANS\" witout quotes   in the matrix letter." << endl;
    cout << "Example : \n to do A+B-C , add A+B then sub ANS-C \n to do inv(A)*C , get inverse A then multiply  ANS * C ." << endl;
    cout << "\n" << endl;

    bool ACTIVE = true;

    char s = 'A';
    while (true)
    {
        cout << "Enter Matrix " << s << " : ";
        getline(cin, matrices[n]);
        if (!validMatrix(matrices[n]))
        {
            cout << "Invalid Matrix " << endl;
            matrices[n] = "";
            continue;
        }
        else
        {
            s++;
            n++;
            break;
        }
    }


    cout << endl;
    while (ACTIVE)
    {
        while (true)
        {
            if (n >= 26)
                break;

            cout << "Type 1 to add another mat or 2 to go to operations or exit to end program" << endl;
            cout << endl;

            string order;
            cin >> order;
            cout << endl;
            if (order == "1")
            {
                cin.ignore();
                while (true)
                {
                    cout << "Enter Matrix " << s << " : ";
                    getline(cin, matrices[n]);
                    if (!validMatrix(matrices[n]))
                    {
                        cout << "Invalid Matrix " << endl;
                        matrices[n] = "";
                    }
                    else
                    {
                        s++;
                        n++;
                        break;
                    }
                }


                cout << endl;
                if (n >= 26)
                    break;
            }
            else if (order == "2")
            {
                break;
            }
            else if (order == "exit")
            {
                cout << "Exiting Now" << endl << endl;
                return 0;
            }
            else
            {
                cout << "Invalid Operation" << endl << endl;
                continue;
            }
        }

        while (true)
        {
            cout << "Choose one of the following operations." << endl << endl;
            cout << "1- Show Matrix Value" << endl;
            cout << "2- Addition" << endl;
            cout << "3- Subtraction" << endl;
            cout << "4- Multiplication" << endl;
            cout << "5- Determinant" << endl;
            cout << "6- Transpose" << endl;
            cout << "7- Inverse" << endl;
            cout << "8- Division" << endl;
            cout << "9- Add more Matrices" << endl;
            cout << "10- Override a Matrix" << endl;
            cout << "11- Exit (Or type exit)" << endl << endl;

            string order;
            cin >> order;
            cout << endl;
            if (order == "1")
            {
                //65
                string mat;
                cout << "Choose mat letter : ";
                cin >> mat;


                if (isLetterValid(mat))
                {
                    //vector<float> elementsA = getElemnts(matrices[matn]);
                    cout << endl << "Matrix " << mat << " :" << endl;

                    string matr = matrices[letterToIndex(mat)];

                    PrintMatrix(GetMatrix(matr, getRows(matr), getColumns(matr)));
                    cout << endl;
                }
                else
                {
                    cout << "Invalid Matrix" << endl << endl;
                }
            }
            else if (order == "2")
            {
                string mat1;
                cout << "Choose first mat letter : ";
                cin >> mat1;
                if (!isLetterValid(mat1))
                {
                    cout << "Invalid Matrix" << endl << endl;
                    continue;
                }
                cout << endl;

                string mat2;
                cout << "Choose second mat letter : ";
                cin >> mat2;
                if (!isLetterValid(mat2))
                {
                    cout << "Invalid Matrix" << endl << endl;
                    continue;
                }

                addition(matrices[letterToIndex(mat1)], matrices[letterToIndex(mat2)]);
            }
            else if (order == "3")
            {
                string mat1;
                cout << "Choose first mat letter : ";
                cin >> mat1;
                if (!isLetterValid(mat1))
                {
                    cout << "Invalid Matrix" << endl << endl;
                    continue;
                }
                cout << endl;

                string mat2;
                cout << "Choose second mat letter : ";
                cin >> mat2;
                if (!isLetterValid(mat2))
                {
                    cout << "Invalid Matrix" << endl << endl;
                    continue;
                }

                subtraction(matrices[letterToIndex(mat1)], matrices[letterToIndex(mat2)]);
            }
            else if (order == "4")
            {
                string choice;
                cout << "For[ Num * Matrix ] Please Enter 1 \t For [Matrix * Matrix] Please enter 2 " << endl;
                cin >> choice;
                cout << endl;
                if (choice == "2")
                {
                    string mat1;
                    cout << "Choose first mat letter : ";
                    cin >> mat1;
                    if (!isLetterValid(mat1))
                    {
                        cout << "Invalid Matrix" << endl << endl;
                        continue;
                    }
                    cout << endl;

                    string mat2;
                    cout << "Choose second mat letter : ";
                    cin >> mat2;
                    if (!isLetterValid(mat2))
                    {
                        cout << "Invalid Matrix" << endl << endl;
                        continue;
                    }

                    multiply(matrices[letterToIndex(mat1)], matrices[letterToIndex(mat2)]);
                }
                else if (choice == "1")
                {
                    string mat1;
                    cout << "Choose first mat letter : ";
                    cin >> mat1;
                    if (!isLetterValid(mat1))
                    {
                        cout << "Invalid Matrix" << endl << endl;
                        continue;
                    }
                    cout << endl;
                    float numb;
                    string nmb;
                    cout << "Enter Multiplication Number : ";
                    cin >> nmb;
                    if (!isInputDigit(nmb))
                    {
                        cout << "\nThis is not a number" << endl << endl;
                        continue;
                    }
                    numb = stof(nmb);
                    multiply_byNum(matrices[letterToIndex(mat1)], numb);
                }
                else {
                    cout << "Something went wrong " << endl;
                    continue;
                }
            }
            else if (order == "5")
            {
                string mat;
                cout << "Choose mat letter : ";
                cin >> mat;


                if (isLetterValid(mat))
                {
                    //vector<float> elementsA = getElemnts(matrices[matn]);

                    string matr = matrices[letterToIndex(mat)];

                    int n = 0;
                    int rows = getRows(matr);
                    int cols = getColumns(matr);
                    vector<vector<float> > mats = GetMatrix(matr, getRows(matr), getColumns(matr));
                    if (rows != cols)
                    {
                        cout << endl << "Matrix " << mat << " doesn't have a determinant" << endl << endl;
                        continue;
                    }
                    n = rows;


                    cout << "The determinant of matrix " << mat << " is: " << determinant(mats, n) << endl;
                    cout << endl;
                }
                else
                {
                    cout << "Invalid Matrix" << endl << endl;
                }
            }
            else if (order == "6")
            {
                string mat;
                cout << "Choose mat letter : ";
                cin >> mat;


                if (isLetterValid(mat))
                {
                    //vector<float> elementsA = getElemnts(matrices[matn]);
                    cout << endl << "Matrix Transpose " << mat << " :" << endl;

                    transpose(matrices[letterToIndex(mat)]);
                }
                else
                {
                    cout << "Invalid Matrix" << endl << endl;
                    continue;
                }
            }
            else if (order == "7")
            {
                string mat;
                cout << "Choose mat letter : ";
                cin >> mat;


                if (isLetterValid(mat))
                {
                    //vector<float> elementsA = getElemnts(matrices[matn]);
                    int Rows1 = getRows(matrices[letterToIndex(mat)]);
                    int Cols1 = getColumns(matrices[letterToIndex(mat)]);
                    if (Rows1 != Cols1)
                    {
                        cout << endl << "Matrix " << mat << " isn't a square matrix" << endl << endl;
                        continue;
                    }
                    if (determinant(GetMatrix(matrices[letterToIndex(mat)], Rows1, Cols1), Rows1) == 0)
                    {
                        cout << endl << "Matrix " << mat << " doesn't have an inverse" << endl << endl;
                        continue;
                    }

                    cout << endl << "Matrix Inverse " << mat << " :" << endl;

                    vector<vector<float>> s = GetMatrix(matrices[letterToIndex(mat)], Rows1, Cols1);
                    inverse(s);
                    cout << endl;
                }
                else
                {
                    cout << "Invalid Matrix" << endl << endl;
                    continue;
                }
            }
            else if (order == "8")
            {
                string mat1;
                cout << "Choose first mat letter : ";
                cin >> mat1;
                if (!isLetterValid(mat1))
                {
                    cout << "Invalid Matrix" << endl << endl;
                    continue;
                }
                cout << endl;

                string mat2;
                cout << "Choose second mat letter : ";
                cin >> mat2;
                if (!isLetterValid(mat2))
                {
                    cout << "Invalid Matrix" << endl << endl;
                    continue;
                }

                divide(matrices[letterToIndex(mat1)], matrices[letterToIndex(mat2)]);
            }
            else if (order == "9")
            {
                break;
            }
            else if (order == "10")
            {
                string mat;
                cout << "Choose mat letter : ";
                cin >> mat;

                cin.ignore();
                while (true)
                {
                    if (isLetterValid2(mat))
                    {
                        cout << "Enter Matrix : " << endl;
                        getline(cin, matrices[letterToIndex(mat)]);
                        if (!validMatrix(matrices[letterToIndex(mat)]))
                        {
                            cout << "Invalid Matrix" << endl;
                            matrices[letterToIndex(mat)] = "";
                            continue;
                        }

                        cout << endl << "Matrix " << mat << " was successfuly overriden" << endl << endl;
                        break;
                    }
                    else
                    {
                        cout << "Invalid Matrix" << endl << endl;
                        break;
                    }
                }
            }
            else if (order == "11" || order == "exit")
            {
                cout << endl << "Exiting Now" << endl << endl;
                ACTIVE = false;
                return 0;
            }
            else
            {
                cout << "Invalid Operation" << endl << endl;
                continue;
            }
        }
    }

    return 0;
}

bool isLetterValid(string l)
{
    if (l.length() == 1)
    {
        int matn = (int)l[0] - 65;
        if (matn >= 0 && matn < 26)
        {
            if (matrices[matn] == "")
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        if (l == "ANS")
        {
            if (matrices[26] == "")
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        else
        {
            return false;
        }
    }

}

int letterToIndex(string l)
{
    if (l.length() == 1)
    {
        int matn = (int)l[0] - 65;
        return matn;
    }
    else
    {
        if (l == "ANS")
        {
            return 26;
        }

        return -1;
    }
}

bool isLetterValid2(string l)
{
    if (l.length() == 1)
    {
        int matn = (int)l[0] - 65;
        if (matn >= 0 && matn < 26)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if (l == "ANS")
        {
            return true;
        }
        else
        {
            return false;
        }
    }

}


void addition(string matA, string matB)
{
    int RowsA = getRows(matA);
    int RowsB = getRows(matB);
    int ColsA = getColumns(matA);
    int ColsB = getColumns(matB);

    if (RowsA == RowsB && ColsA == ColsB)
    {
        //cout << "You can Add the two matrices.\n" << endl;
    }
    else
    {
        cout << endl << "Sorry, You can't add these matrices." << endl << endl;
        return;
    }
    cout << endl << "Addition of Two Matrices :" << endl;

    vector<vector<float> > MatA = GetMatrix(matA, RowsA, ColsA);
    vector<vector<float> > MatB = GetMatrix(matB, RowsB, ColsB);
    vector<vector<float> > MatC = GetMatrix(RowsA, ColsA);

    for (int i = 0; i < MatA.size(); i++)
    {
        for (int j = 0; j < MatA[i].size(); j++)
        {
            MatC[i][j] = MatA[i][j] + MatB[i][j];
        }
    }

    matrices[26] = vectorString(MatC);

    PrintMatrix(MatC);
    cout << endl;
}

void subtraction(string matA, string matB)
{
    int RowsA = getRows(matA);
    int RowsB = getRows(matB);
    int ColsA = getColumns(matA);
    int ColsB = getColumns(matB);

    if (RowsA == RowsB && ColsA == ColsB)
    {
        //cout << "You can subtract the two matrices.\n" << endl;
    }
    else
    {
        cout << endl << "Sorry, You can't subtract these matrices." << endl << endl;
        return;
    }
    cout << endl << "Subtraction of Two Matrices :" << endl;

    vector<vector<float> > MatA = GetMatrix(matA, RowsA, ColsA);
    vector<vector<float> > MatB = GetMatrix(matB, RowsA, ColsA);
    vector<vector<float> > MatC = GetMatrix(RowsA, ColsA);

    for (int i = 0; i < MatA.size(); i++)
    {
        for (int j = 0; j < MatA[i].size(); j++)
        {
            MatC[i][j] = MatA[i][j] - MatB[i][j];
        }
    }

    matrices[26] = vectorString(MatC);


    PrintMatrix(MatC);
    cout << endl;
}

void transpose(string mat)
{
    cout << endl << "Transpose of Matrix :" << endl;
    int RowsA = getRows(mat);
    int ColsA = getColumns(mat);

    vector<vector<float> > MatA = GetMatrix(mat, RowsA, ColsA);
    vector<vector<float> > MatB = GetMatrix(ColsA, RowsA);

    for (int i = 0; i < MatA.size(); i++)
    {
        for (int j = 0; j < MatA[i].size(); j++)
        {
            MatB[j][i] = MatA[i][j];
        }
    }

    matrices[26] = vectorString(MatB);


    PrintMatrix(MatB);
    cout << endl;
}
void multiply(string matA, string matB) {
    int RowsA = getRows(matA);
    int RowsB = getRows(matB);
    int ColsA = getColumns(matA);
    int ColsB = getColumns(matB);
    if (ColsA == RowsB)
    {
        //cout << "You can multiply the two matrices.\n" << endl;
    }
    else
    {
        cout << endl << "Sorry, You can't Multiply these matrices." << endl << endl;
        return;
    }
    cout << endl << "Multiplication of Two Matrices :" << endl;

    vector<vector<float> > MatA = GetMatrix(matA, RowsA, ColsA);
    vector<vector<float> > MatB = GetMatrix(matB, RowsB, ColsB);
    vector<vector<float> > MatC = GetMatrix(RowsA, ColsB);


    for (int i = 0; i < RowsA; ++i)
    {
        for (int j = 0; j < ColsB; ++j)
        {
            for (int k = 0; k < ColsA; ++k)
            {
                MatC[i][j] += MatA[i][k] * MatB[k][j];
            }
        }
    }

    matrices[26] = vectorString(MatC);


    PrintMatrix(MatC);
    cout << endl;
}
void multiply_byNum(string matA, float num) {
    int RowsA = getRows(matA);
    int ColsA = getColumns(matA);
    vector<vector<float> > MatC = GetMatrix(matA, RowsA, ColsA);
    cout << endl << "Multiplication result is :" << endl;
    for (int i = 0; i < RowsA; ++i)
    {
        for (int j = 0; j < ColsA; ++j)
        {
            MatC[i][j] *= num;
        }
    }
    matrices[26] = vectorString(MatC);
    PrintMatrix(MatC);
    cout << endl;
}

void divide(string matA, string matB) {

    int RowsA = getRows(matA);
    int RowsB = getRows(matB);
    int ColsA = getColumns(matA);
    int ColsB = getColumns(matB);
    if (RowsA == ColsA && RowsA == RowsB && RowsA == ColsB)
    {
        //cout << "You can multiply the two matrices.\n" << endl;
    }
    else
    {
        cout << endl << "Sorry, You can't Divide these matrices." << endl << endl;
        return;
    }

    vector<vector<float> > MatA = GetMatrix(matA, RowsA, ColsA);
    if (determinant(GetMatrix(matB, RowsB, ColsB), RowsB) == 0.0)
    {
        cout << endl << "Sorry, the determinant of the second matrix is 0 " << endl << endl;
        return;
    }
    vector<vector<float> > MatB = GetInverse(GetMatrix(matB, RowsB, ColsB));
    vector<vector<float> > MatC = GetMatrix(RowsA, ColsB);


    for (int i = 0; i < RowsA; ++i)
    {
        for (int j = 0; j < ColsB; ++j)
        {
            for (int k = 0; k < ColsA; ++k)
            {
                MatC[i][j] += MatA[i][k] * MatB[k][j];
            }
        }
    }

    matrices[26] = vectorString(MatC);


    PrintMatrix(MatC);
    cout << endl;
}

bool isInputDigit(string digitss) {

    for (int i = 0; i < digitss.length(); i++)
    {
        if (!isdigit(digitss[i]))
        {
            if (digitss[i] != '.')
            {
                return false;
            }
        }
    }
    return true;
}


float determinant(vector<vector<float>> mat, int n)
{
    float determn = 0;
    vector<vector<float>> temp = GetMatrix(n, n);
    if (n == 1)
    {
        return mat[0][0];
    }
    else if (n == 2)
    {
        determn = (mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0]);
        return determn;
    }
    else
    {
        for (int w = 0; w < n; w++)
        {
            int e = 0;
            int f = 0;
            for (int i = 1; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (j == w)
                    {
                        continue;
                    }
                    temp[e][f] = mat[i][j];
                    f++;
                    if (f == n - 1)
                    {
                        e++;
                        f = 0;
                    }
                }
            }
            determn = determn + mat[0][w] * pow(-1, w) * determinant(temp, n - 1);
        }
        return determn;
    }
}
vector<vector<float>> cofactor(vector<vector<float>> mat)
{
    int n = mat.size();
    vector<float> tempElements;
    vector<vector<float>> temp;
    int n_temp = n - 1;

    vector<vector<float>> cof = GetMatrix(n, n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                if (k == i)
                {
                    continue;
                }
                for (int l = 0; l < n; l++)
                {
                    if (l == j)
                    {
                        continue;
                    }
                    tempElements.push_back(mat[k][l]);
                }
            }
            temp = GetMatrix(tempElements, n_temp, n_temp);
            cof[i][j] = pow(-1, i + j) * determinant(temp, n_temp);
            tempElements.clear();
        }
    }
    return cof;
}
vector<vector<float>> transpose_vector(vector<vector<float>> mat)
{
    int RowsA = mat.size();
    int ColsA = mat[0].size();
    vector<vector<float> > MatB = GetMatrix(ColsA, RowsA);
    for (int i = 0; i < RowsA; i++)
    {
        for (int j = 0; j < ColsA; j++)
        {
            MatB[j][i] = mat[i][j];
        }
    }
    return MatB;
}

vector<vector<float>> multiply_byNum_vector(vector<vector<float>> matA, float num) {
    int RowsA = matA.size();
    int ColsA = matA[0].size();
    vector<vector<float>> matC = GetMatrix(RowsA, ColsA);
    for (int i = 0; i < RowsA; ++i)
    {
        for (int j = 0; j < ColsA; ++j)
        {
            matA[i][j] *= num;
        }
    }
    return matA;
}

void inverse(vector<vector<float> > mat)
{
    int n = mat.size();
    vector<vector<float> > Adj;
    vector<vector<float> > MatB;
    if (determinant(mat, n) == 0)
    {
        cout << "Cant get inverse as Determinant = 0 " << endl << endl;
    }
    Adj = cofactor(mat);
    Adj = transpose_vector(Adj);
    cout << endl;
    MatB = multiply_byNum_vector(Adj, 1 / determinant(mat, n));

    matrices[26] = vectorString(MatB);
    PrintMatrix(MatB);
    cout << endl;
}

vector<vector<float> > GetInverse(vector<vector<float> > mat)
{
    int n = mat.size();
    vector<vector<float> > Adj;
    vector<vector<float> > MatB;
    if (determinant(mat, n) == 0)
    {
        cout << "Cant get inverse as Determinant = 0 " << endl << endl;
    }
    Adj = cofactor(mat);
    Adj = transpose_vector(Adj);
    cout << endl;
    MatB = multiply_byNum_vector(Adj, 1 / determinant(mat, n));

    return MatB;
}