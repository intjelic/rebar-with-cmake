-module(yolo).

-export([abc/0, abc/1]).
-nifs([abc_raw/1]).

-on_load(init/0).

-define(APPNAME, rebar_with_cmake).

init() ->
    io:format("yolo:init:aaa~n"),
    LibName = "beam-yolo",
    SoName = case code:priv_dir(?APPNAME) of
        {error, bad_name} ->
            io:format("yolo:init:bbb~n"),
            case filelib:is_dir(filename:join(["..", priv])) of
                true ->
                    io:format("yolo:init:ccc~n"),
                    filename:join(["..", priv, LibName]);
                _ ->
                    io:format("yolo:init:ddd~n"),
                    filename:join([priv, LibName])
            end;
        Dir ->
            io:format("yolo:init:eeee~n"),
            filename:join(Dir, LibName)
    end,
    io:format("Loading 'yolo' NIF from ~s~n", [SoName]),
    erlang:load_nif(SoName, 0).

abc() ->
    abc("Erlangsters").

abc(Name) ->
    abc_raw(Name).

abc_raw(Name) ->
    erlang:nif_error(nif_library_not_loaded).
