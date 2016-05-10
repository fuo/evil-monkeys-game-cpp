//
//  drawEngine.hpp
//  evil-monkeys
//
//  Created by phuong on 5/10/16.
//  Copyright © 2016 badila. All rights reserved.
//

#ifndef drawEngine_hpp
#define drawEngine_hpp

class DrawEngine
{
public:
    DrawEngine(int screenW = 600, int screenH = 400);
    ~DrawEngine();
    
    int createSprite(int figureIndex, char img);
    bool deleteSprite(int figureIndex);
    
    bool eraseSprite(int xpos, int ypos);
    bool drawSprite(int figureIndex, int xpos, int ypos);
    
protected:
    int screenWidth, screenHeight;
    
    char spriteImages[16];
    
private:
    bool gotoxy(int xpos, int ypos);
    bool cursorVisibility(bool visibility);
    
};

#endif /* drawEngine_hpp */
