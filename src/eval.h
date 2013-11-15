struct LispObj              *eval(struct LispObj *sexpr, struct Env *env);
struct LispObj *eval_special_form(struct LispObj *sexpr, struct Env *env);
