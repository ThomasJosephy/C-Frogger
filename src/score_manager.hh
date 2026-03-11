#pragma once
#include <fstream>
#include <string>

class ScoreManager {
public:
    // Charge le meilleur score depuis le fichier
    static int loadBestScore() {
        ensureFileExists();
        std::ifstream file("best_score.txt");
        int score = 0;
        if (file) {
            file >> score;
        }
        return score;
    }

    // Sauvegarde le meilleur score dans le fichier
    static void saveBestScore(int score) {
        ensureFileExists();
        std::ofstream file("best_score.txt");
        if (file.is_open()) {
            file << score;
            file.close();
        }
    }

    // Réinitialise le meilleur score à 0
    static void resetBestScore() {
        saveBestScore(0);
    }

private:
    // Vérifie si le fichier existe, sinon le crée avec un score initial de 0
    static void ensureFileExists() {
        std::ifstream file("best_score.txt");
        if (!file.is_open()) {
            std::ofstream outFile("best_score.txt");
            outFile << 0;
            outFile.close();
        }
    }
};
