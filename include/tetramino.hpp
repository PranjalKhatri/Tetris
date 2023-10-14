#ifndef __TETRAMINO_HPP__
#define __TETRAMINO_HPP__
#include <vector>
using namespace std;
class Tetramino
{
private:
    int m_height;
    int m_width;
    vector<vector<int>> m_piece;
    int  m_tblocks = 0;
    Tetramino* m_nextpiece = nullptr;

private:
    void ComputeNextRotation(void);
public:
    void SetVars(int h, int w, char* arr);
    Tetramino(int height, int width, char* arr);
    Tetramino() {};
    int GetWidth(void) { return m_width; }
    int GetHeight(void) { return m_height; }
    /*vector<int> Getskirt(void) { return m_skirt; }*/
    vector<vector<int>> GetPiece(void) { return m_piece; }
    void SetNextPiece(Tetramino* t) { this->m_nextpiece = t; }
    Tetramino* GetRotatedPiece(void);
    // bool operator==(Tetramino& t);
    ~Tetramino(void);
};




#endif