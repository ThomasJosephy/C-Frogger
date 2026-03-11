for(auto &c:cars) {
c.draw();
if (checkCollision(f, c)) {
if (!frogHit) {
f.loseLife();
f.spawn();
f.setRow(1);
frogHit = true;  // La grenouille a été touchée, définir l'état de la collision à true
}
} else {
frogHit = false;  // Réinitialiser l'état de la collision si la grenouille n'est pas en collision
}
}