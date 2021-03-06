#ifndef GAMELOADER_H
#define GAMELOADER_H

#include <QStringList>

#include "nes.h"


class GameLoader
{
public:
    GameLoader(NES* nes);

public:
    bool LoadGame(const QString& filename);
    const QStringList& RecentGames();

private:
    NES* mNes = nullptr;
    QStringList mRecent;
};

#endif // GAMELOADER_H
