#include <iostream>
#include <string>
#include <sstream>
#include <typeinfo>

class Command {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
};

//! Null Object
class NoCommand : public Command {
public:
    void execute() {}
    void undo() {}
};

//! Receiver
class Light {
public:
    Light(std::string lightName) : lightName(lightName) {}
    void on() const { std::cout << lightName << " light is on" << std::endl; }
    void off() const { std::cout << lightName << " light is off" << std::endl; }
    
private:
    std::string lightName;
};

class CeilingFan {
public:
    CeilingFan(std::string fanName) : fanName(fanName) {}
    void high() const { std::cout << fanName << " fan is on high" << std::endl; }
    void off() const { std::cout << fanName << " fan is off" << std::endl; }

private:
    std::string fanName;
};

class LightOnCommand : public Command {
public:
    LightOnCommand(Light* light) {  this->light = light; }
    ~LightOnCommand() { delete light; }
    void execute() { light->on(); }
    void undo() {   light->off(); }
    
private:
    Light* light;
};

class LightOffCommand : public Command {
public:
    LightOffCommand(Light* light) { this->light = light; }
    ~LightOffCommand() { delete light; }
    void execute() { light->off(); }
    void undo() {   light->on(); }
    
private:
    Light* light;
};

class CeilingFanOnCommand : public Command {
public:
    CeilingFanOnCommand(CeilingFan* ceilingFan) { this->ceilingFan = ceilingFan; }
    ~CeilingFanOnCommand() { delete ceilingFan; }
    void execute() { ceilingFan->high(); }
    void undo() { ceilingFan->off(); }
    
private:
    CeilingFan* ceilingFan;
};

class CeilingFanOffCommand : public Command {
public:
    CeilingFanOffCommand(CeilingFan* ceilingFan) { this->ceilingFan = ceilingFan; }
    ~CeilingFanOffCommand() { delete ceilingFan; }
    void execute() { ceilingFan->off(); }
    void undo() {   ceilingFan->high(); }
    
private:
    CeilingFan* ceilingFan;
};

//! Invoker
class RemoteControl {
public:
    RemoteControl() {
        onCommands = new Command*[7]; // must add if changed to ** 1
        offCommands = new Command*[7]; // must add if changed to ** 2

        Command* noCommand = new NoCommand();
        for(int i =0; i < 7; i++) {
            onCommands[i] = noCommand;
            offCommands[i] = noCommand;
        }
        undoCommand = noCommand;
        std::cout << "dotu1" << std::endl;
    }
    
    void setCommand (int slot, Command* onCommand, Command* offCommand) {
        onCommands[slot] = onCommand;
        offCommands[slot] = offCommand;
    }
    
    void onButtonWasPushed(int slot) {
        onCommands[slot]->execute();
        undoCommand = onCommands[slot];
    }
    
    void offButtonWasPushed(int slot) {
        offCommands[slot]->execute();
        undoCommand = offCommands[slot];
    }
    
    void undoButtonWasPushed() const {
        undoCommand->undo();
    }
    
    std::string toString() const {
        std::stringstream sStream;
        
        sStream << std::endl << "------ Remote Control ------" << std::endl;
        for(int i = 0; i < 7; i++) {
            sStream << "[slot " << i << "] " << typeid(*onCommands[i]).name() << "    " << typeid(*offCommands[i]).name() << std::endl;
        }
        sStream << "[undo] " << typeid(*undoCommand).name() << std::endl;
        
        return sStream.str();
    }

private:
    // Command* onCommands[7]; // must comment if changed to ** 3
    // Command* offCommands[7]; // must comment if changed to ** 4
    Command** onCommands; // must add if changed to ** 5
    Command** offCommands; // must add if changed to ** 6
    Command* undoCommand;
    
};

/*
 * COMMAND PATTERN encapsulates request as an object, thereby letting you parameterize
 *   other objects with different requests, queue or log requests and supports undoable operations.
 */
//! Client
int main() {
    RemoteControl* remote = new RemoteControl();
    
    remote->setCommand(0, new LightOnCommand(new Light("Living Room")), new LightOffCommand(new Light("Living Room")));
    remote->setCommand(1, new CeilingFanOnCommand(new CeilingFan("Kitchen")), new CeilingFanOffCommand(new CeilingFan("Kitchen")));
    
    std::cout << remote->toString() << std::endl;

    remote->onButtonWasPushed(0);
    remote->offButtonWasPushed(0);
    remote->onButtonWasPushed(1);
    remote->offButtonWasPushed(1);
    remote->undoButtonWasPushed();
    
    delete remote;
    
    return 0;
}
