//
// Created by Denys Ksenchuk <denny.ks359@gmail.com>
//

#ifndef SIMPLEGAMES_MATRIX_HPP
#define SIMPLEGAMES_MATRIX_HPP


#include <QRectF>

#include "tile.hpp"


class Node {

public:
    enum LinkDirection {
        TOP,
        RIGHT,
        BOTTOM,
        LEFT
    };

    void setLink(LinkDirection dir, Node* ptr) {
        switch (dir) {
            case TOP:
                top = ptr;
                break;
            case RIGHT:
                right = ptr;
                break;
            case BOTTOM:
                bottom = ptr;
                break;
            case LEFT:
                left = ptr;
                break;
        }
    }

    Node* getLink(LinkDirection dir) {
        Node* ptr = nullptr;
        switch (dir) {
            case TOP:
                ptr = top;
                break;
            case RIGHT:
                ptr = right;
                break;
            case BOTTOM:
                ptr = bottom;
                break;
            case LEFT:
                ptr = left;
                break;
        }
        return ptr;
    }

    const Tile::RectType& geometry() const {return target_geometry;}
    void setTargetGeometry(const Tile::RectType& rect) {target_geometry = rect;}
    void setTargetGeometry(Tile::RectCoord x,
                           Tile::RectCoord y,
                           Tile::RectCoord width,
                           Tile::RectCoord height) {
        target_geometry.setRect(x, y, width, height);
    }

private:
    Tile tile;
    Tile::RectType target_geometry;
    Node* top = nullptr;
    Node* right = nullptr;
    Node* bottom = nullptr;
    Node* left = nullptr;

};

class Matrix {

public:
    explicit Matrix(int res) {
        data = new Node[res * res];
        if (data) {
            mx_size = res * res;
            mx_res = res;
            for (int offset = 0; offset < mx_size; offset++) {
                if (offset % res) {
                    data[offset].setLink(Node::LEFT, data + offset - 1);
                    data[offset - 1].setLink(Node::RIGHT, data + offset);
                }
                if (offset >= res) {
                    data[offset].setLink(Node::TOP, data + offset - res);
                    data[offset - res].setLink(Node::BOTTOM, data + offset);
                }
            }
        }
    }
    ~Matrix() {delete[] data;}

    Node* begin() {return data;}
    Node* end() {return data + mx_size;}

    void updateGeometry(Tile::RectCoord spacing, Tile::RectCoord cell_width) {
        for (int x = 0; x < mx_res; x++) {
            for (int y = 0; y < mx_res; y++) {
                data[x + y * mx_res].setTargetGeometry(
                        (x + 1) * spacing + x * cell_width,
                        (y + 1) * spacing + y * cell_width,
                        cell_width,
                        cell_width);
            }
        }
    }

private:
    Node* data = nullptr;
    int mx_res = 0;
    int mx_size = 0;
};


#endif //SIMPLEGAMES_MATRIX_HPP
