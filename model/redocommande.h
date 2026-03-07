#ifndef REDOCOMMANDE_H
#define REDOCOMMANDE_H
#include "MandalaModel.h"
#include "Command.h"

class RedoCommande : public Command
{
public:
    RedoCommande(MandalaModel model) : _model(model) {};
    void execute() override;
private:
    MandalaModel _model;
};

#endif // REDOCOMMANDE_H
