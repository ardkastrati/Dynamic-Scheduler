class AbstractExecuter {
    private:

    public:
        virtual void execute() = 0;
        static AbstractExecuter get_new_executer_by_id(int rank,
            int number_of_processors);

}
