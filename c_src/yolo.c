#include <string.h>
#include <assert.h>
#include <erl_nif.h>

ERL_NIF_TERM undefined_atom;

static int nif_module_load(ErlNifEnv *env, void **priv_data, ERL_NIF_TERM arg)
{
    (void)priv_data;
    (void)arg;

    printf("nif_module_load\n");

    return 0;
}

static void nif_module_unload(ErlNifEnv* caller_env, void* priv_data)
{
    (void)caller_env;
    (void)priv_data;

    printf("nif_module_unload\n");
}

static ERL_NIF_TERM nif_abc(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
    if (argc != 1) {
        return enif_make_badarg(env);
    }

    unsigned len;
    if (!enif_get_list_length(env, argv[0], &len) && !enif_is_binary(env, argv[0])) {
        // Try to get string length for atom or other string-like term
        if (!enif_get_atom_length(env, argv[0], &len, ERL_NIF_LATIN1)) {
            return enif_make_badarg(env);
        }
    }

    char name[256];
    if (enif_is_binary(env, argv[0])) {
        ErlNifBinary bin;
        if (!enif_inspect_binary(env, argv[0], &bin)) {
            return enif_make_badarg(env);
        }
        if (bin.size >= sizeof(name)) {
            return enif_make_badarg(env);
        }
        memcpy(name, bin.data, bin.size);
        name[bin.size] = '\0';
    } else if (!enif_get_string(env, argv[0], name, sizeof(name), ERL_NIF_LATIN1)) {
        return enif_make_badarg(env);
    }

    printf("Hello, %s!\n", name);

    return enif_make_int(env, 42);
}

static ErlNifFunc nif_functions[] = {
    {"abc_raw", 1, nif_abc, 0}
};

ERL_NIF_INIT(
    yolo,
    nif_functions,
    nif_module_load,
    NULL,
    NULL,
    nif_module_unload
);
