-module(yolo).

-export([abc/1]).
-nifs([abc_raw/1]).

-on_load(init/0).

init() ->
    LibName = "beam-yolo",
    SoName = case code:priv_dir(?MODULE) of
        {error, bad_name} ->
            case filelib:is_dir(filename:join(["..", priv])) of
                true ->
                    filename:join(["..", priv, LibName]);
                _ ->
                    filename:join([priv, LibName])
            end;
        Dir ->
            filename:join(Dir, LibName)
    end,
    io:format("Loading 'yolo' NIF from ~s~n", [SoName]),
    erlang:load_nif(SoName, 0).

abc(Name) ->
    abc_raw(Name).

abc_raw(Name) ->
    erlang:nif_error(nif_library_not_loaded).
