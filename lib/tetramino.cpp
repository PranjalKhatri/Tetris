#include "..\include\tetramino.hpp"

Tetramino::Tetramino(int height, int width, char* arr)
{
    SetVars(height, width, arr);
    
}
void Tetramino::SetVars(int h, int w, char* arr) {
    m_height = h;
    m_width = w;
    for (int i = 0; i < m_height; i++)
    {
        m_piece.push_back(vector<int>(m_width,0));
    }

    for (int i = 0; i < (m_height * m_width); i++)
    {
        if (arr[i] == '\0') {
            break;
        }
        else {
            int a = (arr[i] - '0');
            m_tblocks++;
            m_piece[int(a / m_width)][int(a % m_width)] = 1;
        }
    }
}

void Tetramino::ComputeNextRotation(void) {
    char arr[m_tblocks + 1];
    int k = 0;
    // std::cout<<m_tblocks<<std::endl;
    for (int i = 0; i < m_height; i++)
    {
        for (int j = 0; j < m_width; j++)
        {
            if (m_piece[i][j] == 1) {
                int x = j;
                int y = i;
                // int temp;
                int temp = x;
                x = -y;
                y = temp;
                x += (m_height - 1);
                temp = x;
                x = y;
                y = temp;
                int pos = ((m_height * (x)) + y);
                // cout << "x = " << x << " y = " << y << " pos " << pos << endl;
                arr[k] = char(pos);
                arr[k] += '0';
                // std::cout << pos << " " << arr[k] << " k " << k << std::endl;
                k++;
            }
        }
        // std::cout << "\n";
    }
    arr[k] = '\0';
    Tetramino* rotated = new Tetramino(m_width, m_height, arr);
    m_nextpiece = rotated;
}

Tetramino* Tetramino::GetRotatedPiece(void)
{
    if (this->m_nextpiece == nullptr) {
        ComputeNextRotation();
    }
    return this->m_nextpiece;
}

// bool Tetramino::operator==(Tetramino& t) {
//     if (t.m_height != m_height && t.m_width != m_width) {
//         return false;
//     }
//     vector<int> b = t.m_piece;
//     for (int i = 0; i < m_height; i++)
//     {
//         for (int j = 0; j < m_width; j++)
//         {
//             if (b[i][j] != m_piece[i][j]) {
//                 return false;
//             }
//         }

//     }
//     return true;
// }

Tetramino::~Tetramino()
{
    m_piece.clear();
}