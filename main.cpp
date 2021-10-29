//#include <bits/stdc++.h>
#include "SDL.h"

#include "Visualization.h"
#include "Steering.h"

using namespace std;


int main(int argc, char* argv[]) {

    Visualization vis = Visualization();

    if (!vis.IsWindowCreated()){
        return 1;
    }

    if (!vis.IsRendererCreated()){
        return 1;
    }

    if (!vis.IsFontLoaded()){
        return 1;
    }

    vis.DrawScene();

    vis.GameNameText();

    vis.ScoreText();


    while (true)
    {
        vis.RunTheGame();
    }

    vis.~Visualization();

    return 0;
}