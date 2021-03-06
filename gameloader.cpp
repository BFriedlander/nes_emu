#include "gameloader.h"
#include "json.h"

#include <fstream>
#include <string>

#include <QDebug>


GameLoader::GameLoader(NES *nes)
{
    mNes = nes;

    std::ifstream i("recents.json");
    if (!i.is_open()) return;
    json j;
    i >> j;

    if (j.contains("recents"))
    {
        for (auto& r : j["recents"])
        {
            std::string rs = r;
            mRecent.append(QString(rs.c_str()));
        }
    }
}

bool GameLoader::LoadGame(const QString& filename)
{
    if (!mNes->LoadGame(filename.toStdString()))
        return false;

    if (mRecent.contains(filename))
        mRecent.removeAll(filename);

    mRecent.insert(0, filename);
    if (mRecent.size() > 10)
        mRecent.removeLast();

    json j;
    for (auto& r : mRecent)
    {
        j.push_back(r.toStdString());
    }
    json d;
    d["recents"] = j;

    std::ofstream o("recents.json");
    o << d;

    return true;
}

const QStringList &GameLoader::RecentGames()
{
    return mRecent;
}
