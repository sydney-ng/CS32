//
//  mazestack.h
//  Homework2
//
//  Created by Super on 2/2/18.
//  Copyright © 2018 Sydney. All rights reserved.
//

#ifndef mazestack_h
#define mazestack_h

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

#endif /* mazestack_h */
