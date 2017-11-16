#include <iostream>

class Action
{
	public:
        virtual void Execute(void)=0;

};

class Model
{
    private:
        int m_tick;
    public:
        Model(){ m_tick = 0; };
        int getTick(){ return ++m_tick; };
};

class Context
{
    private:
        Model* m_model;
    public:
        Context(Model* model): m_model(model){};
        void update()
        {
            std::cout << "context update and get the new tick: " << m_model->getTick() << std::endl;
        }
};

class UpdateAction : public Action
{
	private:
        Context* c;
        void Execute() { c->update(); };
//        virtual void Execute() { c->update(); };
	public:
        UpdateAction(Context* context) : c(context){ Execute(); };
//        virtual void Execute() { c->update(); };
};

int main()
{
    Model* model = new Model;
    Context* context = new Context(model);
    UpdateAction* action1 = new UpdateAction(context);
    UpdateAction* action2 = new UpdateAction(context);
    UpdateAction* action3 = new UpdateAction(context);
    UpdateAction* action4 = new UpdateAction(context);
}
