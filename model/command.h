#ifndef COMMAND_H
#define COMMAND_H

class Command
{
public:
    Command();
    virtual void execute();
    virtual ~Command() = default;
};

#endif // COMMAND_H
