type direction_t =
  | Stretch
  | Start
  | Center
  | Between
  | End;

module Styles = {
  open Css;

  let row = style([display(`flex), flex(`num(1.)), width(`percent(100.))]);

  let justify =
    fun
    | Start => style([justifyContent(`flexStart)])
    | Center => style([justifyContent(`center)])
    | Between => style([justifyContent(`spaceBetween)])
    | End => style([justifyContent(`flexEnd)])
    | _ => style([justifyContent(`flexStart)]);

  let alignItems =
    fun
    | Stretch => style([alignItems(`stretch)])
    | Start => style([alignItems(`flexStart)])
    | Center => style([alignItems(`center)])
    | End => style([alignItems(`flexEnd)])
    | _ => style([alignItems(`stretch)]);

  let wrap = style([flexWrap(`wrap)]);

  let minHeight = mh => style([minHeight(mh)]);
  let rowBase = style([display(`flex), margin2(~v=`zero, ~h=`px(-12))]);

  let marginBottom = size => {
    style([marginBottom(`px(size))]);
  };
};

[@react.component]
let make = (~justify=Start, ~alignItems=?, ~minHeight=`auto, ~wrap=false, ~style="", ~children) => {
  <div
    className={Css.merge([
      Styles.row,
      Styles.justify(justify),
      Styles.minHeight(minHeight),
      Css.style([Css.alignItems(alignItems->Belt.Option.getWithDefault(`center))]),
      wrap ? Styles.wrap : "",
      style,
    ])}>
    children
  </div>;
};

module Grid = {
  [@react.component]
  let make =
      (
        ~justify=Start,
        ~alignItems=Stretch,
        ~minHeight=`auto,
        ~wrap=true,
        ~style="",
        ~children,
        ~marginBottom=0,
      ) => {
    <div
      className={Css.merge([
        Styles.rowBase,
        Styles.justify(justify),
        Styles.minHeight(minHeight),
        Styles.alignItems(alignItems),
        Styles.marginBottom(marginBottom),
        wrap ? Styles.wrap : "",
        style,
      ])}>
      children
    </div>;
  };
};
