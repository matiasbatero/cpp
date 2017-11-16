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

        void change()
        {
            ++m_tick;
        };

        int getTick(){ return m_tick; };
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

class Context2
{
    private:
        Model* m_model;
    public:
        Context2(Model* model): m_model(model){};
        void update()
        {
            std::cout << "context 2 update and get the new tick: " << m_model->getTick() << std::endl;
        }
};

class UpdateAction : public Action
{
	private:
        Context* c;
        void Execute() { c->update(); };

	public:
        UpdateAction(Context* context) : c(context){ Execute(); };
};

int main()
{
    Model* model = new Model;
    Context* context = new Context(model);
    Context2* context2 = new Context2(model);

    model->change();
    UpdateAction* updateAction1 = new UpdateAction(context);

    UpdateAction* updateActionForContext2 = new UpdateAction(context2);

    model->change();
    UpdateAction* updateAction2 = new UpdateAction(context);

    model->change();
    UpdateAction* updateAction3 = new UpdateAction(context);

    model->change();
    UpdateAction* updateAction4 = new UpdateAction(context);
}
