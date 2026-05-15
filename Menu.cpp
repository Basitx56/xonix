#include <cmath>
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "main.h"
#include <time.h>
#include <string>

using namespace sf;
using namespace std;


// ------------------ HELPER FUNCTIONS ------------------

void drawMenu(RenderWindow& window, Font& font, Text menu[Max_menu]) {
    for (int i = 0; i < Max_menu; i++) {
        
        menu[i].setFillColor(Color(169, 169, 169));

        window.draw(menu[i]);
    }
}

void moveUp(int& menuSelected, int Max_menu) {
    
    (menuSelected == 0)? menuSelected = Max_menu - 1: menuSelected--; 
   
}

void moveDown(int& menuSelected, int Max_menu) {
   
    (menuSelected == Max_menu - 1)? menuSelected = 0 :menuSelected++;
   
}

void drawCommonUI(RenderWindow* window, Sprite& background, Sprite& logo) {
    if (background.getTexture())
        window->draw(background);
    if (logo.getTexture())
        window->draw(logo);
}

// ------------------ SHOW SCORE BOARD ------------------

void showScoreBoard(RenderWindow* window) {
    // Load font
    Font font;
    if (!font.loadFromFile("Fonts/OpenSans.ttf")) {
        cout << "Font not loaded!" << endl;
        return;
    }

    

    // Read scores from file
    string lines[5];
    ifstream infile("scores.txt");
    int i = 0;
    while (i < 5  ) {
        getline(infile, lines[i]);

        i++;
    }
    infile.close();

    // Clear screen
    window->clear(Color::Black);

    Texture backgroundTexture;
    Sprite background;
     if (backgroundTexture.loadFromFile("images/Black.jpeg"))
        background.setTexture(backgroundTexture);


    Texture titleTexture;
    Sprite title;
    if (titleTexture.loadFromFile("images/SCORE-TITLE.png")) {
        title.setTexture(titleTexture);
        title.setPosition(150, 10);
        title.setScale(350.0f / title.getLocalBounds().width, 150.0f / title.getLocalBounds().height);

        
    }
    drawCommonUI(window, background, title);


    Text test("(Press  Ecs to exit)", font, 20);
    test.setFillColor(Color::Yellow);
    test.setPosition(200, 400);
    window->draw(test);


    
   
    // Display each score on score board
    for (int j = 0; j < i; j++) {
        Text scoreText(lines[j], font, 28);
        scoreText.setFillColor(Color::White);
        scoreText.setPosition(200, 120 + j * 40); // space between scores
        window->draw(scoreText);
    }
    
    window->display();

    // Wait for key press to exit scoreboard
    while (true) {
        Event event;
        while (window->pollEvent(event)) {
            if (event.type == Event::KeyPressed || event.type == Event::Closed  ) {
                return;
            }
        }
    }
}





// ------------------  GENERIC SUB-MENU RENDERER ------------------
int showSubmenu(RenderWindow* window, const string options[], int count) {
    int selected = 0;

    Font font;
    if (!font.loadFromFile("Fonts/AlexandriaFLF.ttf")) {
        cout << "Font loading failed!" << endl;
        return -1;
    }

    // Load background image
    Texture backgroundTexture;
    Sprite background;
    if (backgroundTexture.loadFromFile("images/background.jpg"))
        background.setTexture(backgroundTexture);

    // Load logo image
    Texture logoTexture;
    Sprite logo;
    if (logoTexture.loadFromFile("images/logo.png")) {
        logo.setTexture(logoTexture);
        logo.setPosition(30, 120);
        logo.setScale(350.0f / logo.getLocalBounds().width, 90.0f / logo.getLocalBounds().height);
    }

    // Setup text for each option
    Text optionText[10];  // Max 10 menu items
    for (int i = 0; i < count; i++) {
        optionText[i].setFont(font);
        optionText[i].setCharacterSize(20);
        optionText[i].setFillColor(Color(169, 169, 169));  // Default gray
        optionText[i].setString(options[i]);
        optionText[i].setPosition(60, 230 + i * 30);  // Position options vertically
    }

    // Selector highlight box
    RectangleShape selector(Vector2f(200, 25));
    selector.setFillColor(Color(128, 128, 128, 150));  // Semi-transparent gray

    // Menu loop
    while (window->isOpen()) {
        Event event;
        while (window->pollEvent(event)) {
            if (event.type == Event::Closed)
                window->close();

            if (event.type == Event::KeyReleased) {
                if (event.key.code == Keyboard::Up)
                    moveUp(selected, count);
                else if (event.key.code == Keyboard::Down)
                    moveDown(selected, count);
                else if (event.key.code == Keyboard::Return)
                    return selected;  // Return selected index to caller function
            }
        }

        // Drawing the UI
        window->clear();
        drawCommonUI(window, background, logo);

        // Draw selector on selected option
        selector.setPosition(55, 230 + selected * 30);
        window->draw(selector);

        // Draw menu options with hover effect
        for (int i = 0; i < count; i++) {
            optionText[i].setFillColor(i == selected ? Color::White : Color(169, 169, 169));
            window->draw(optionText[i]);
        }

        window->display();
    }

    return -1;  // If window is closed or ESC is pressed
}



// ------------------ SUB-MENU ------------------

     int mode = 1; // default mode is single player
void showGameMode(RenderWindow* window) {
    string options[] = { "Single Player", "Multiplayer", "Back" };
    int choice = showSubmenu(window, options, 3);
      
    if (choice == 0) {
        mode = 1;
        showMenu(window);  // Re-show menu after returning
    }
    else if (choice == 1) {
        mode = 2;
        showMenu(window);  // Re-show menu after returning
    }
    // If choice == 2, user selected "Back", so simply return to caller
}
    
      int difficulty = 1; // default difficulty is easy
void showDifficulty(RenderWindow* window) {
    string options[] = { "Easy", "Medium", "Hard", "Continous", "Back" };

    int choice = showSubmenu(window, options, 5);
       
    if (choice == 0) {
        difficulty = 1;
        showMenu(window);  // Re-show menu after returning
    }
    else if (choice == 1) {
        difficulty = 2;
        showMenu(window);  // Re-show menu after returning
    }
    else if (choice == 2) {
        difficulty = 3;
        showMenu(window);  // Re-show menu after returning
    }
    else if (choice == 3) {
        difficulty = 4;
        showMenu(window);  // Re-show menu after returning
    }
    // If choice == 4, user selected "Back", so simply return to caller
}

    int sound  = 1; // default mode sound on 
void showSound(RenderWindow* window) {
    string options[] = { "Sound Off", "Sound On", "Back" };
    int choice = showSubmenu(window, options, 3);

    
    if (choice == 0) {
        sound = 0; // 
        showMenu(window);  //  return to main menu after returning
    }
    else if (choice == 1) {
        sound = 1;
        showMenu(window);  // Return to main menu after returning
    }
    // If choice == 2, user selected "Back", so simply return to caller
}


     int reset   = 0; // default mode sound on 
void showResetSettings(RenderWindow* window) {
        string options[] = { "Confirm", "Cancel" };
        int choice =  showSubmenu(window, options, 2);
        if (choice == 0) {
        reset = 1; // 
        showMenu(window);  //  return to main menu after returning
    }
     // If choice == 1, user selected "Cancel", so simply return to caller
}





// ------------------ OPTION MENU ------------------

void showOptions(RenderWindow* window) {
    int selected = 0;
    string options[] = { "GAME MODE", "DIFFICULTY","SCORE BOARD" ,"SOUND", "RESET SETTINGS", "BACK" };
    int count = 6;

    Font font;
    if (!font.loadFromFile("Fonts/AlexandriaFLF.ttf")) {
        cout << "Font loading failed!" << endl;
        return;
    }

    // Background & Logo
    Texture backgroundTexture;
    Sprite background;
    if (backgroundTexture.loadFromFile("images/background.jpg"))
        background.setTexture(backgroundTexture);

    Texture logoTexture;
    Sprite logo;
    if (logoTexture.loadFromFile("images/logo.png")) {
        logo.setTexture(logoTexture);
        logo.setPosition(30, 120);
        logo.setScale(350.0f / logo.getLocalBounds().width, 90.0f / logo.getLocalBounds().height);
        
    }

    Text texts[10];
    for (int i = 0; i < count; ++i) {
        texts[i].setFont(font);
        texts[i].setCharacterSize(20);
        texts[i].setFillColor(Color(169, 169, 169));
        texts[i].setString(options[i]);
        texts[i].setPosition(60, 230 + i * 30);
    }

    RectangleShape selector(Vector2f(200, 25));
    selector.setFillColor(Color(128, 128, 128, 150));

    while (window->isOpen()) {
        Event event;
        while (window->pollEvent(event)) {
            if (event.type == Event::Closed)
                window->close();
            if (event.type == Event::KeyReleased) {
                if (event.key.code == Keyboard::Up  )
                 moveUp(selected, count);
                else if (event.key.code == Keyboard::Down )
                moveDown(selected, count);
                else if (event.key.code == Keyboard::Return) {
                    if (selected == 0) showGameMode(window);
                    else if (selected == 1) showDifficulty(window);
                    else if (selected == 2) showScoreBoard(window);
                    else if (selected == 3) showSound(window);
                    else if (selected == 4) showResetSettings(window);
                    else if (selected == 5) return;
                }
            }
        }

        window->clear();
        drawCommonUI(window, background, logo);

        selector.setPosition(55, 230 + selected * 30);
        window->draw(selector);

        for (int i = 0; i < count; i++) {
            texts[i].setFillColor(i == selected ? Color::White : Color(169, 169, 169));
            window->draw(texts[i]);
        }

        window->display();
    }
}




// ------------------ MAIN MENU ------------------

void showMenu(RenderWindow* window) {
    int selected = 0;  // index selected

    Font font;
    if (!font.loadFromFile("Fonts/AlexandriaFLF.ttf")) {
        cout << "Font loading failed!" << endl;
        return;
    }

    Text menu[Max_menu];
    string items[Max_menu] = { "PLAY", "OPTIONS", "ABOUT", "EXIT" };
    for (int i = 0; i < Max_menu; ++i) {
        menu[i].setFont(font);
        menu[i].setCharacterSize(20);
        // Set default text color to gray using RGB (169, 169, 169)
        menu[i].setFillColor(Color(169, 169, 169));
        menu[i].setString(items[i]);
        menu[i].setPosition(60, 230 + i * 30);
    }

    RectangleShape selector(Vector2f(200, 25));
    selector.setFillColor(Color(128, 128, 128, 150));
    selector.setPosition(55, 230);

    Texture backgroundTexture;
    Sprite background;
    if (backgroundTexture.loadFromFile("images/background.jpg"))
        background.setTexture(backgroundTexture);

    Texture logoTexture;
    Sprite logo;
    if (logoTexture.loadFromFile("images/logo.png")) {
        logo.setTexture(logoTexture);
        logo.setPosition(30, 120);
        logo.setScale(350.0f / logo.getLocalBounds().width, 90.0f / logo.getLocalBounds().height);
    }

    while (window->isOpen()) {
        Event event;
        while (window->pollEvent(event)) { // event listner 
            if (event.type == Event::Closed)
                window->close();
            if (event.type == Event::KeyReleased) {
                if (event.key.code == Keyboard::Up)
                    moveUp(selected, Max_menu);
                else if (event.key.code == Keyboard::Down)
                    moveDown(selected, Max_menu);
                else if (event.key.code == Keyboard::Return) {
                    if (selected == 0) {
                        if (mode == 1){
                            SingleGame(window, difficulty);
                          }
                             else if(mode == 2) {
                                   MultiGame(window, difficulty);
                                   }
                    } else if (selected == 1) {
                        showOptions(window);
                    } else if (selected == 2) {
                        cout<<"DEVELOPED BY BASIT & AYESHA"<<endl;
                    } else if (selected == 3) {
                        window->close();
                    }
                }
            }
        }

        window->clear();
        drawCommonUI(window, background, logo);

        selector.setPosition(55, 230 + selected * 30);
        window->draw(selector);

        // Update text colors for hover effect (selected option turns white)
        for (int i = 0; i < Max_menu; i++) {
            if (i == selected) {
                menu[i].setFillColor(Color::White);  // Hover color (white)
            } else {
                menu[i].setFillColor(Color(169, 169, 169));   // Default color (gray)
            }
            window->draw(menu[i]);
        }

        window->display();
    }
}



// ------------------ PAUSE MENU ------------------

void showPauseMenu(RenderWindow* window) {
    int selected = 0;

    Font font;
    if (!font.loadFromFile("Fonts/AlexandriaFLF.ttf")) {
        cout << "Font loading failed!" << endl;
        return;
    }

    Text menu[pauseMenu];
    string items[pauseMenu] = { "RESUME", "RESTART", "MAIN MENU", "EXIT" };
    for (int i = 0; i < pauseMenu; i++) {
        menu[i].setFont(font);
        menu[i].setCharacterSize(20);
        // Set default text color to gray using RGB (169, 169, 169)
        menu[i].setFillColor(Color(169, 169, 169));
        menu[i].setString(items[i]);
        menu[i].setPosition(60, 230 + i * 30);
    }

    RectangleShape selector(Vector2f(200, 25));
    selector.setFillColor(Color(128, 128, 128, 150));
    selector.setPosition(55, 230);

    Texture backgroundTexture;
    Sprite background;
    if (backgroundTexture.loadFromFile("images/background.jpg"))
        background.setTexture(backgroundTexture);

    Texture logoTexture;
    Sprite logo;
    if (logoTexture.loadFromFile("images/logo.png")) {
        logo.setTexture(logoTexture);
        logo.setPosition(30, 120);
        logo.setScale(350.0f / logo.getLocalBounds().width, 80.0f / logo.getLocalBounds().height);
    }

    while (window->isOpen()) {
        Event event;
        while (window->pollEvent(event)) {
            if (event.type == Event::Closed)
                window->close();
            if (event.type == Event::KeyReleased) {
                if (event.key.code == Keyboard::Up)
                    moveUp(selected, pauseMenu);
                else if (event.key.code == Keyboard::Down)
                     moveDown(selected, pauseMenu);
                else if (event.key.code == Keyboard::Return) {
                    if (selected == 0) {
                        return; // return to contine game 
                    } else if (selected == 1) {
                       if (mode == 1){
                            SingleGame(window, difficulty);
                          }
                             else if(mode == 2) {
                                   MultiGame(window, difficulty);
                                   }
                    } else if (selected == 2) {
                       showMenu(window);
                    } else if (selected == 3) {
                        window->close();
                    }
                }
            }
        }

        window->clear();
        drawCommonUI(window, background, logo);

        selector.setPosition(55, 230 + selected * 30);
        window->draw(selector);

        // Update text colors for hover effect (selected option turns white)
        for (int i = 0; i < pauseMenu; i++) {
            if (i == selected) {
                menu[i].setFillColor(Color::White);  // Hover color (white)
            } else {
                menu[i].setFillColor(Color(169, 169, 169));   // Default color (gray)
            }
            window->draw(menu[i]);
        }

        window->display();
    }
} 


// ------------------ END MENU  ------------------
void showEndMenu(RenderWindow* window, int score) {
    int selected = 0;

    // Load font
    Font font;
    if (!font.loadFromFile("Fonts/AlexandriaFLF.ttf")) {
        cout << "Font loading failed!" << endl;
        return;
    }

    // Load background
    Texture backgroundTexture;
    Sprite background;
    if (backgroundTexture.loadFromFile("images/background.jpg"))
        background.setTexture(backgroundTexture);

    // Load game over image
    Texture gameOverTexture;
    Sprite gameOver;
    if (gameOverTexture.loadFromFile("images/gameover.png")) {
        gameOver.setTexture(gameOverTexture);
        gameOver.setPosition(120, 50);
    }

    // Score text
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(35);
    scoreText.setString("Your Score: " + to_string(score));
    scoreText.setFillColor(Color::Yellow);
    scoreText.setPosition(250, 190);

    // High score text
    Text highScoreText;
    highScoreText.setFont(font);
    highScoreText.setCharacterSize(24);
    highScoreText.setFillColor(Color::Green);
    highScoreText.setPosition(60, 220);

    // Check if score is in top 5
    int scores[5];
    int count = 0;
    ifstream infile("scores.txt");
    while (infile >> scores[count] && count < 5) {
        count++;
    }
    infile.close();

    bool isHighScore = false;
    if (count < 5 || score > scores[count - 1]) {
        isHighScore = true;
        highScoreText.setString("New High Score!");
    }

    // Menu options
    const int options = 3;
    string items[options] = { "RESTART", "MAIN MENU", "EXIT" };
    Text menu[options];

    for (int i = 0; i < options; i++) {
        menu[i].setFont(font);
        menu[i].setCharacterSize(20);
        menu[i].setFillColor(Color(169, 169, 169));
        menu[i].setString(items[i]);
        menu[i].setPosition(60, 270 + i * 30);
    }

    RectangleShape selector(Vector2f(200, 25));
    selector.setFillColor(Color(128, 128, 128, 150));
    selector.setPosition(55, 270);

    while (window->isOpen()) {
        Event event;
        while (window->pollEvent(event)) {
            if (event.type == Event::Closed)
                window->close();
            if (event.type == Event::KeyReleased) {
                if (event.key.code == Keyboard::Up)
                    moveUp(selected, options);
                else if (event.key.code == Keyboard::Down)
                    moveDown(selected, options);
                else if (event.key.code == Keyboard::Return) {
                    if (selected == 0) {
                        SingleGame(window, difficulty);
                    } else if (selected == 1) {
                        showMenu(window);
                    } else if (selected == 2) {
                        window->close();
                    }
                }
            }
        }

        window->clear();
        drawCommonUI(window, background, gameOver);

        window->draw(scoreText);
        if (isHighScore)
            window->draw(highScoreText);

        selector.setPosition(55, 270 + selected * 30);
        window->draw(selector);

        for (int i = 0; i < options; i++) {
            if (i == selected)
                menu[i].setFillColor(Color::White);
            else
                menu[i].setFillColor(Color(169, 169, 169));
            window->draw(menu[i]);
        }

        window->display();
    }
}

void showMEndMenu(RenderWindow* window, int score,  string string) {
    int selected = 0;

    // Load font
    Font font;
    if (!font.loadFromFile("Fonts/AlexandriaFLF.ttf")) {
        cout << "Font loading failed!" << endl;
        return;
    }

    // Load background
    Texture backgroundTexture;
    Sprite background;
    if (backgroundTexture.loadFromFile("images/background.jpg"))
        background.setTexture(backgroundTexture);

    // Load game over image
    Texture gameOverTexture;
    Sprite gameOver;
    if (gameOverTexture.loadFromFile("images/gameover.png")) {
        gameOver.setTexture(gameOverTexture);
        gameOver.setPosition(120, 50);
    }

    // Score text
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(35);
    scoreText.setString(string + " Score: " + to_string(score));
    scoreText.setFillColor(Color::Yellow);
    scoreText.setPosition(250, 190);

    // High score text
    Text winner;
    winner.setFont(font);
    winner.setCharacterSize(24);
    winner.setFillColor(Color::Green);
    winner.setPosition(60, 220);
    winner.setString(string);
    

   

    // Menu options
    const int options = 3;
    std::string items[options] = { "RESTART", "MAIN MENU", "EXIT" };
    Text menu[options];

    for (int i = 0; i < options; i++) {
        menu[i].setFont(font);
        menu[i].setCharacterSize(20);
        menu[i].setFillColor(Color(169, 169, 169));
        menu[i].setString(items[i]);
        menu[i].setPosition(60, 270 + i * 30);
    }

    RectangleShape selector(Vector2f(200, 25));
    selector.setFillColor(Color(128, 128, 128, 150));
    selector.setPosition(55, 270);

    while (window->isOpen()) {
        Event event;
        while (window->pollEvent(event)) {
            if (event.type == Event::Closed)
                window->close();
            if (event.type == Event::KeyReleased) {
                if (event.key.code == Keyboard::Up)
                    moveUp(selected, options);
                else if (event.key.code == Keyboard::Down)
                    moveDown(selected, options);
                else if (event.key.code == Keyboard::Return) {
                    if (selected == 0) {
                       if(mode == 1) SingleGame(window, difficulty);
                       else if(mode == 2) MultiGame(window, difficulty);
                    } else if (selected == 1) {
                        showMenu(window);
                    } else if (selected == 2) {
                        window->close();
                    }
                }
            }
        }

        window->clear();
        drawCommonUI(window, background, gameOver);

        window->draw(scoreText);
       
        

        selector.setPosition(55, 270 + selected * 30);
        window->draw(selector);

        for (int i = 0; i < options; i++) {
            if (i == selected)
                menu[i].setFillColor(Color::White);
            else
                menu[i].setFillColor(Color(169, 169, 169));
            window->draw(menu[i]);
        }

        window->display();
    }
}