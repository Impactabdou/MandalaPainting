#include "redocommande.h"

void RedoCommande::execute(){
    _model.setCurrentIdx(_model.getCurrentIdx()+ 1);
}
